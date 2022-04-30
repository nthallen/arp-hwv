/* @file icosfitd.cc 
 * icosfitd will run as a standard 3-interface driver. Scan number,
 * pressure and temperature will be provided by a TMA algorithm and
 * sent via the usual command channels (cmd/icosfitd in this case).
 *
 * We will need to provide an icosfit configuration file that
 * defines where output should be written. We will use FIFOs
 * for PTEFile and OutputFile
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <spawn.h>
#include <stdio.h>
#include "icosfitd_int.h"
#include "msg.h"
#include "nl_assert.h"
#include "oui.h"

/**
 * These paths need to match between the icosfit file and the
 * driver. The experimenter needs to know where the icosfit
 * file is stored so it can be updated easily. (It should
 * probably be stored in $TMBINDIR!)
 */
const char *PTE_FIFO_PATH = "PTE.fifo";
const char *ICOSsum_FIFO_PATH = "ICOSsum.fifo";

const char *icosfit_file_in;
const char *icosfit_file_out;
bool log_icossum = false;
int line_search[2] = {400, 650};
const char *scan_ibase = "SSP";
const char *column_list;
const char *command_file;
int max_coadd = 0;

void set_icosfit_file(bool is_output, const char *path) {
  if (is_output) {
    if (icosfit_file_out)
      msg(3, "Only one icosfit file can be specified on the command line");
    icosfit_file_out = path;
  } else if (icosfit_file_in) {
    msg(3, "Only one icosfit file can be specified on the command line");
  } else {
    icosfit_file_in = path;
  }
}

void set_line_search(const char *range) {
  if (sscanf(range, "%d:%d", &line_search[0], &line_search[1]) != 2) {
    msg(3, "Invalid line search range specified");
  }
  if (line_search[0] >= line_search[1]) {
    msg(3, "Line search range must be non-empty");
  }
}

icos_pipe::icos_pipe(bool input, int bufsize,
        const char *path, const char *logfile, fitd *fit)
    : Ser_Sel(),
      is_ready(false),
      is_input(input),
      in_the_loop(false),
      path(path),
      logfp(0),
      fit(fit),
      res(0)
{
  if (logfile) {
    logfp = fopen(logfile, "a");
    if (logfp) {
      fprintf(logfp, "# icosfitd %s log file\n",
        is_input ? "input" : "output");
    } else {
      msg(MSG_ERROR, "Unable to write to %s log file %s",
        is_input ? "input" : "output", logfile);
    }
  }
  if (bufsize) {
    buf = (unsigned char *)new_memory(bufsize);
    this->bufsize = bufsize;
  }
  flags = 0;
}

icos_pipe::~icos_pipe() {
  cleanup();
}

int icos_pipe::ProcessData(int flag) {
  if (flag & Selector::Sel_Timeout) {
    TO.Clear();
    flags &= ~Selector::Sel_Timeout;
    if (is_ready) {
      msg(MSG_ERROR, "Unexpected timeout when ready");
      flags &= ~Selector::Sel_Timeout;
    } else if (is_input) {
      nl_assert(fd >= 0 && !is_ready);
      msg(-2, "input pipe: timeout to check if ready");
      flag |= Selector::Sel_Read;
    } else {
      nl_assert(fd < 0 && !is_ready);
      msg(-2, "output pipe: timeout to check if ready");
      return open_pipe();
    }
  }
  if (flag & Selector::Sel_Write) {
    if (!is_input) {
      msg(MSG, "Pipe %s ready for output", path);
      is_ready = true;
      if (fit && fit->PTE_ready())
        return 1;
    }
    flags &= ~Selector::Sel_Write;
  }
  if (flag & Selector::Sel_Read) {
    if (is_input) {
      cp = 0;
      ++n_fills;
      int i = read( fd, &buf[nc], bufsize - 1 - nc );
      if (i < 0) {
        if (errno == EAGAIN) {
          msg(-2, "input pipe: read now returns EAGAIN, dropping TO");
          nl_assert(!is_ready);
          TO.Clear();
          is_ready = true;
          flags = Selector::Sel_Read;
          return 0;
        } else if (errno == EINTR) {
          ++n_eintr;
        } else {
          msg(MSG_ERROR,
            "Error %d on read from serial port", errno);
          return 1;
        }
        return 0;
      }
      if (i == 0) {
        if (is_ready) {
          msg(MSG_ERROR,
            "Zero bytes from icosfit: probably terminated");
          is_ready = false;
          Stor->set_gflag(1);
        }
        msg(-2, "input pipe: read zero bites, setting TO");
        TO.Set(1,0);
        flags = Selector::Sel_Timeout;
      } else {
        if (!is_ready) {
          msg(-2, "input pipe: receiving data");
          TO.Clear();
          is_ready = true;
          flags = Selector::Sel_Read;
        }
        nc += i;
        buf[nc] = '\0';
        return protocol_input();
      }
    } else {
      int i = read( fd, &buf[nc], bufsize - 1 - nc );
      if (i < 0) {
        msg(-2, "read from output pipe return error %d: %s",
          errno, strerror(errno));
      } else {
        msg(-2, "read from output pipe returned %d bytes", i);
      }
      flags &= ~Selector::Sel_Read;
    }
  }
  return 0;
}

int icos_pipe::protocol_input() {
  char *nl = strchr((char *)buf, '\n');
  if (!res) {
    report_err("Unexpected input before results initialized");
    consume(nc);
    return 0;
  }
  if (nl) {
    unsigned int ncl = nl+1-(char*)buf;
    nl_assert(ncl <= nc);
    unsigned char savec = buf[ncl];
    buf[ncl] = '\0';
    if (logfp) {
      fprintf(logfp, "%s", buf);
      fflush(logfp);
    }
    buf[ncl] = savec;
    int first, scannum;
    float P, T, val;
    if ((max_coadd &&
          (not_int(first) ||
           not_whitespace())) ||
        not_int(scannum) ||
        not_whitespace() ||
        not_float(P) ||
        not_whitespace() ||
        not_float(T)) {
      report_err("Format error in ICOSsum.dat");
      res->Status = res_Syntax;
    } else {
      if ((uint32_t)scannum != res->scannum)
        msg(1, "Result expected scannum %ld, received %ld", res->scannum, scannum);
      res->scannum = (uint32_t)scannum;
      res->P = P;
      res->T = T;
      int res_num = 0;
      int cur_col = 4 + (max_coadd ? 1 : 0);
      for (; cp < ncl && buf[cp] != '\n'; ++cur_col) {
        if (not_whitespace() || not_float(val)) {
          report_err("Expected float");
          res->Status = res_Syntax;
          break;
        }
        if (cur_col == res->ValIdxs[res_num]) {
          res->Vals[res_num++] = val;
          if (res_num >= res->n_Vals) break;
        }
      }
      if (res_num < res->n_Vals) {
        report_err("Reached end of line without finding all results");
        res->Status = res_Syntax;
      }
      res->Status = res_Fit;
    }
    consume(nc);
    if (fit && fit->process_results(res))
      return 1;
    if (res->Status == res_Fit)
      report_ok();
  }
  return 0;
}

void icos_pipe::output(const char *line) {
  int nbline = strlen(line);
  if (logfp) {
    fprintf(logfp, "%s", line);
    fflush(logfp);
  }
  int rc = write(fd, line, nbline);
  if (rc < 0) {
    msg(MSG_ERROR, "Error %d writing to %s: %s",
      errno, path, strerror(errno));
  } else if (rc < nbline) {
    msg(MSG_ERROR, "Partial line output to %s", path);
  }
}

void icos_pipe::cleanup() {
  close();
  unlink(path);
}

void icos_pipe::set_result(results *r) {
  if (! is_input) {
    msg(3, "icos_pipe::set_result() illegal for output");
  } else {
    res = r;
  }
}

int icos_pipe::setup_pipe() {
  msg(-2, "icos_pipe::setup_pipe(%s)", is_input ? "input" : "output");
  cleanup();
  if (mkfifo(path, 0664) != 0) {
    msg(MSG_ERROR, "%s: mkfifo error %d: %s",
      path, errno, strerror(errno));
  }
  // could use init() here, but it can only be called once
  // without creating a memory leak on buf
  if (is_input) {
    if (open_pipe()) return 1;
    if (fit && !in_the_loop) {
      fit->add_child(this);
      in_the_loop = true;
    }
  }
  return 0;
}

int icos_pipe::open_pipe() {
  fd = open(path, (is_input?O_RDONLY:O_WRONLY)|O_NONBLOCK);
  if (fd < 0) {
    if (is_input) {
      msg(MSG_FATAL, "%s: error %d opening for read: %s",
        path, errno, strerror(errno));
    } else {
      msg(-2, "output pipe: unable to open, setting TO");
      TO.Set(1,0);
      flags = Selector::Sel_Timeout;
      if (fit && !in_the_loop) {
        fit->add_child(this);
        in_the_loop = true;
      }
    }
    return 0;
  } else if (!is_input) {
    msg(-2, "output pipe: open and ready");
    is_ready = true;
    flags = Selector::Sel_Write;
    // if (fit && fit->check_queue())
    //   return 1;
  } else {
    flags = Selector::Sel_Read;
  }
  return 0;
}

void icos_pipe::close() {
  if (fd >= 0) {
    ::close(fd);
    fd = -1;
    flags = 0;
    is_ready = false;
  }
}

Timeout *icos_pipe::GetTimeout() {
  return &TO;
}

int icos_pipe::logfd() {
  return logfp ? fileno(logfp) : -1;
}

int icos_pipe::not_whitespace() {
  if (cp >= nc || !isspace(buf[cp]))
    return 1;
  while (cp < nc && isspace(buf[cp])) {
    ++cp;
  }
  return 0;
}

icos_TM::icos_TM(const char *name, void *data, unsigned short size)
    : TM_Selectee(name, data, size) {
  msg(-2, "icos_TM() fd = %d, flags = %d", fd, flags);
}

int icos_TM::ProcessData(int flag) {
  msg(-3, "icos_TM::ProcessData(%d)", flag);
  Col_send(TMid);
  results::posted();
  Stor->set_gflag(0);
  return 0;
}

fitd::fitd()
  : 
    PTE(false, 80, "PTE.fifo", "PTE.log", this),
    SUM(true, 1024, "ICOSsum.fifo", "ICOSsum.log", this),
    CMD(this),
    TM(0),
    ICOSf(scan_ibase),
    fitting_scannum(0),
    next_scannum(0),
    icosfit_status(IFS_Gone),
    icosfit_pid(0)
{
  if (!command_file) {
    int TMsize = sizeof(icosfitd) -
      (MAX_ICOSFITD_RESULT_VALS - results::n_results())
        * sizeof(ICOS_Float);
    msg(-2, "TMsize = %d", TMsize);
    TM = new icos_TM("icosfitd", &icosfitd, TMsize);
    add_child(TM);
  }
  
  int policy;
  pthread_getschedparam(pthread_self(), &policy, &spawn_sched_param);
  msg(-2, "policy is %d, my_priority = %d", policy,
          spawn_sched_param.sched_priority);
  --spawn_sched_param.sched_priority;
  if (pthread_setschedparam(pthread_self(), policy,
                            &spawn_sched_param))
    msg(2, "Error %d setting priority: %s",
      errno, strerror(errno));
}

fitd::~fitd() {}

void fitd::add_child(Selectee *P) {
  msg(-2, "add_child()");
  S.add_child(P);
}

int fitd::scan_data(results *r, const char *PTparams) {
  msg(-2, "scan_data(%ld)", r->scannum);
  if (r->scannum < next_scannum)
    return 0;
  if (icosfitd.Status == IFS_Gone &&
      launch_icosfit(r->scannum)) {
    return 1;
  }
  if (icosfitd.Status == IFS_Ready && PTE.is_ready) {
    r->Status = res_Fitting;
    SUM.set_result(r);
    fitting_scannum = r->scannum;
    char PTEline[256];
    // assumes newline has been removed from PTparams
    if (max_coadd) {
      uint32_t first = r->scannum - max_coadd + 1;
      if (next_scannum) {
        if (next_scannum > first) first = next_scannum;
      } else first = r->scannum;
      snprintf(PTEline, 256, "%u %u %.2f %.1f %s\n", first, fitting_scannum,
        r->P, r->T, PTparams);
    } else {
      snprintf(PTEline, 256, "%u %.2f %.1f %s\n", fitting_scannum,
        r->P, r->T, PTparams);
    }
    next_scannum = fitting_scannum+1;
    PTE.output(PTEline);
    icosfitd.Status = icosfit_status = IFS_Fitting;
    r->update_TM();
    return 0;
  } else {
    msg(-2, "Did not send scan %ld: Status=%d, PTE %s",
      r->scannum, icosfitd.Status, PTE.is_ready ? "ready" : "not ready");
  }
  return 0;
}

int fitd::process_results(results *res) {
  switch (res->Status) {
    case res_Fit:
      msg(-2, "%u: Successfully fit", res->scannum);
      icosfitd.Status = icosfit_status = IFS_Ready;
      break;
    case res_Syntax:
      msg(3, "Syntax error response from icosfit");
      break;
    case res_EOF:
      break;
    default:
      msg(2, "Unexpected result status %d", res->Status);
      break;
  }
  res->finalize();
  return CMD.check_queue();
}

int fitd::PTE_ready() {
  return CMD.check_queue();
}

int fitd::recover() {
  msg(-2, "fitd::recover()");
  PTE.cleanup();
  SUM.cleanup();
  icosfitd.Status = icosfit_status = IFS_Gone;
  results *res = results::active;
  if (res) {
    res->Status = res_EOF;
    return process_results(res);
  } else {
    msg(2, "fitd::recover() but !active");
    return 0;
  }
}

int fitd::launch_icosfit(uint32_t scannum) {
  int linepos = find_line_position(scannum);
  generate_icosfit_file(linepos);
  if (SUM.setup_pipe() ||
      PTE.setup_pipe()) {
    return 1;
  }
  if (spawn_icosfit()) {
    icosfitd.Status = icosfit_status = IFS_Ready;
  }
  return PTE.open_pipe();
}

/**
 * Locate the line position in the specified scan file.
 * @param scannum The starting scan number
 * @return 1-based line position or 0 if there is no scan range.
 */
int fitd::find_line_position(uint32_t scannum) {
  if (! ICOSf.read(scannum)) return 0;
  int start = line_search[0]-MLBASE;
  int end = line_search[1]-MLBASE;
  if (ICOSf.sdata->n_data < end) end = ICOSf.sdata->n_data;
  if (start >= end || start < 0) return 0;
  ICOS_Float detrend_offset = ICOSf.sdata->data[start];
  ICOS_Float detrend_slope =
    (ICOSf.sdata->data[end]-detrend_offset) / (end-start);
  ICOS_Float min_value = 0.;
  int min_sample = start;
  for (int sample = start; sample <= end; ++sample) {
    ICOS_Float trend = detrend_offset + (sample-start)*detrend_slope;
    ICOS_Float detrend = ICOSf.sdata->data[sample] - trend;
    if (detrend < min_value) {
      min_value = detrend;
      min_sample = sample;
    }
  }
  return min_sample + MLBASE;
}

void fitd::generate_icosfit_file(int linepos) {
  char buf[256];
  // open icosfit_file_in
  // In each line, look for Position=%d
  FILE *ifp = fopen(icosfit_file_in, "r");
  if (ifp == 0)
    msg(MSG_FATAL, "Cannot read from icosfit configuration input file '%s'",
        icosfit_file_in);
  FILE *ofp = fopen(icosfit_file_out, "w");
  if (ofp == 0)
    msg(MSG_FATAL, "Cannot write to icosfit configuration output file '%s'",
        icosfit_file_out);
  while (fgets(buf, 255, ifp)) {
    if (strstr(buf, "Position=%d")) {
      fprintf(ofp, buf, linepos);
    } else {
      fprintf(ofp, "%s", buf);
    }
  }
  fclose(ifp);
  fclose(ofp);
}

int fitd::spawn_icosfit() {
  int rv = 1;
  pid_t pid;
  const char *argv[3];
  posix_spawn_file_actions_t fact;
  argv[0] = "/usr/local/bin/icosfit";
  argv[1] = icosfit_file_out;
  argv[2] = 0;
  
  if (posix_spawn_file_actions_init(&fact))
    msg(3, "posix_spawn_file_actions_init returned err %d: %s",
      errno, strerror(errno));
  // PTE is not open while launching
  if (posix_spawn_file_actions_addclose(&fact,SUM.fd) ||
      (SUM.logfd() >= 0 &&
       posix_spawn_file_actions_addclose(&fact,SUM.logfd())) ||
      (CMD.fd >= 0 &&
       posix_spawn_file_actions_addclose(&fact,CMD.fd)) ||
      (PTE.logfd() >= 0 &&
       posix_spawn_file_actions_addclose(&fact,PTE.logfd())) ||
      (TM && TM->fd >= 0 &&
       posix_spawn_file_actions_addclose(&fact,CMD.fd)) ||
      (memo_fp &&
       posix_spawn_file_actions_addclose(&fact,fileno(memo_fp))) ||
      (file_fp &&
       posix_spawn_file_actions_addclose(&fact,fileno(file_fp)))) {
    msg(3, "psfa_addclose returned error %d: %s",
      errno, strerror(errno));
  }

  if (posix_spawn(&pid, argv[0], &fact, 0, (char*const*)argv, 0) < 0) {
    msg(2, "spawn returned error %d: %s", errno, strerror(errno));
    rv = 0;
  }

  if (posix_spawn_file_actions_destroy(&fact))
    msg(2, "posix_spawn_file_actions_destroy returned err %d: %s",
      errno, strerror(errno));
  return rv;
}

icos_cmd::icos_cmd(fitd *fit)
    : Ser_Sel(),
      fit(fit),
      PTparams(0),
      PTparams_len(0),
      cur_scannum(0),
      prev_scannum(0),
      ifp(0)
{
  if (command_file) {
    ifp = fopen(command_file, "r");
    if (ifp == 0)
      msg(3, "Unable to open command_file %s", command_file);
    init(0, 0, 300);
    fd = fileno(ifp);
  } else {
    init(tm_dev_name("cmd/icosfitd"), O_RDONLY, 300);
    msg(-2, "icos_cmd returned from init(). fd = %d, flags = %d",
      fd, flags);
  }
  flags |= Selector::gflag(0) | Selector::gflag(1);
  fit->add_child(this);
}

bool icos_cmd::not_uint32(uint32_t &output_val) {
  uint32_t val = 0;
  if (isdigit(buf[cp])) {
    while (isdigit(buf[cp])) {
      val = val*10 + buf[cp++] - '0';
    }
  } else {
    if (cp < nc)
      report_err("not_uint32: no digits at col %d", cp);
    return true;
  }
  output_val = val;
  return false;
}

int icos_cmd::ProcessData(int flag) {
  if (flag & Selector::gflag(0)) {
    if (!results::active && submit())
      return 1;
  }
  if (flag & Selector::gflag(1)) {
    msg(-2, "icos_cmd: gflag(1)");
    if (fit->recover())
      return 1;
  }
  if (flag & Selector::Sel_Read) {
    if (fillbuf()) return 1;
    return protocol_input();
  }
  return 0;
}

int icos_cmd::protocol_input() {
  cp = 0;
  if (cp < nc && buf[cp] == 'S') {
    int rv = 0;
    if (not_str("S:") ||
        not_uint32(cur_scannum) || not_str(",") ||
        not_float(P) || not_str(",") ||
        not_float(T) || not_str("\n")) {
      if (cp < nc)
        report_err("Invalid 'S' command");
      consume(nc);
      return 0;
    }
    msg(-2, "icos_cmd: S %u\n", cur_scannum);
    rv = submit();
    consume(nc);
    report_ok();
    return rv;
  }
  if (cp < nc && buf[cp] == 'P') {
    if (not_str("P:")) {
      if (cp < nc)
        report_err("Invalid 'P' command");
      consume(nc);
      return 0;
    }
    for (unsigned int endp = cp; endp < nc; ++endp) {
      if (buf[endp] == '\n') {
        int PT_len = endp - cp;
        if (PT_len >= PTparams_len) {
          if (PTparams) {
            nl_free_memory(PTparams);
          }
          PTparams = (char *)new_memory(PT_len+1);
          PTparams_len = PT_len+1;
        }
        strncpy(PTparams, (char*)&buf[2], PT_len);
        PTparams[PT_len] = '\0';
        msg(-2, "icos_cmd: PT params: %s\n",PTparams);
        report_ok();
        consume(++endp);
        return 0;
      }
    }
    report_err("No newline in 'P' command");
    consume(nc);
    return 0;
  }
  if ((cp < nc && buf[cp] == 'Q') || nc == 0) {
    nl_error(0, "Received Quit command");
    consume(nc);
    report_ok();
    return 1;
  }
  if (cp < nc && buf[cp] == 'D') {
    msg(0, "Received kill icosfit command");
    consume(nc);
    report_ok();
    fit->kill_icosfit();
    return 0;
  }
  report_err("Invalid command syntax");
  consume(nc);
  return 0;
}

int icos_cmd::check_queue() {
  // Read commands from the input file a line at a time
  // Stop once a scan has been sent to fitd
  if (results::queued()) {
    return fit->scan_data(results::active, PTparams);
  }
  if (submit()) return 1;
  if (!ifp) return 0;
  int rc = 0;
  if (!results::active) {
    while (icosfitd.Status != IFS_Fitting) {
      if (fgets((char*)buf, bufsize, ifp)) {
        nc = strlen((const char*)buf);
        rc = protocol_input();
        if (rc || buf[0] == 'S')
          return rc;
      } else {
        fclose(ifp);
        ifp = 0;
        fd = -1;
        return 1;
      }
    }
  }
  return rc;
}

int icos_cmd::submit() {
  int rv = 0;
  results *r = 0;
  if (cur_scannum <= prev_scannum)
    return rv;
  if (results::queued()) {
    r = results::active;
    r->reinit(cur_scannum, P, T);
  } else {
    r = results::newres();
    if (r) {
      r->init(cur_scannum, P, T);
    } else {
      msg(-2, "No results for scan %ld", cur_scannum);
    }
  }
  if (r && r->Status == res_Queued && fit->scan_data(r, PTparams)) {
    rv = 1;
  }
  prev_scannum = cur_scannum;
  
  // if (cur_scannum != fitting_scannum) {
    // if (icosfitd.Status != IFS_Fitting) {
      // results *r = results::newres();
      // if (r) {
        // r->init(cur_scannum, P, T);
        // if (fit->scan_data(r, PTparams)) {
          // rv = 1;
        // } else if (icosfitd.Status == IFS_Fitting) {
          // fitting_scannum = cur_scannum;
        // }
      // } else {
        // msg(-2, "No results for scan %ld", cur_scannum);
      // }
    // } else if (results::queued()) {
      // results::active->reinit(cur_scannum, P, T);
    // }
  // }
  return rv;
}

icosfitd_t icosfitd;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (!icosfit_file_in)
    msg(3, "Must specify input icosfit configuration file");
  if (!icosfit_file_out)
    icosfit_file_out = "icosfit.RT";

  results::setup(column_list);
  { fitd fit;
    nl_error(0, "Starting: v1.0");
    if (!fit.check_queue())
      fit.event_loop();
    msg(-2, "Exited from event_loop()");
  }
  nl_error(0, "Terminating");
}
