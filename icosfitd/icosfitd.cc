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
      is_input(input),
      is_ready(false),
      path(path),
      logfp(0),
      fit(fit)
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
  if (is_input)
    res = new results(column_list);
  flags = 0;
}

icos_pipe::~icos_pipe() {
  cleanup();
}

int icos_pipe::ProcessData(int flag) {
  if (flag & Selector::Sel_Timeout) {
    TO.Clear();
    flags &= Selector::Sel_Timeout;
    if (is_ready) {
      msg(MSG_ERROR, "Unexpected timeout when ready");
      flags &= ~Selector::Sel_Timeout;
    } else if (is_input) {
      nl_assert(fd >= 0 && !is_ready);
      flag |= Selector::Sel_Read;
    } else {
      nl_assert(fd < 0 && !is_ready);
      open_pipe();
      return 0;
    }
  }
  if (flag & Selector::Sel_Write) {
    if (!is_input) {
      msg(MSG, "Pipe %s ready for output", path);
      is_ready = true;
    }
    flags &= ~Selector::Sel_Write;
  }
  if (flag & Selector::Sel_Read) {
    if (is_input) {
      unsigned int onc = nc;
      cp = 0;
      ++n_fills;
      int i = read( fd, &buf[nc], bufsize - 1 - nc );
      if (i < 0) {
        if (errno == EAGAIN) {
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
        }
        TO.Set(1,0);
        flags = Selector::Sel_Timeout;
      } else {
        if (!is_ready) {
          TO.Clear();
          is_ready = true;
          flags = Selector::Sel_Read;
        }
        nc += i;
        buf[nc] = '\0';
        return protocol_input();
      }
    } else {
      msg(MSG_WARN,"Unexpected input on output pipe %s", path);
      flags &= ~Selector::Sel_Read;
    }
  }
  return 0;
}

int icos_pipe::protocol_input() {
  char *nl = strchr((char *)buf, '\n');
  if (!nl) {
    unsigned int ncl = nl+1-(char*)buf;
    nl_assert(ncl <= nc);
    unsigned char savec = buf[ncl];
    buf[ncl] = '\0';
    if (logfp) {
      fprintf(logfp, "%s", buf);
    }
    buf[ncl] = savec;
    res->Status = res_OK;
    int scannum;
    float P, T, val;
    if (not_int(scannum) ||
        not_float(P) ||
        not_float(T)) {
      report_err("Format error in ICOSsum.dat");
      res->Status = res_synerr;
    } else {
      int res_num = 0;
      for (int cur_col = 4; cp < ncl && buf[cp] != '\n'; ++cur_col) {
        if (not_float(val)) {
          report_err("Expected float");
          res->Status = res_synerr;
          break;
        }
        if (cur_col == res->ValIdxs[res_num]) {
          res->Vals[res_num++] = val;
          if (res_num >= res->n_Vals) break;
        }
      }
      if (res_num < res->n_Vals) {
        report_err("Reached end of line without finding all results");
        res->Status = res_synerr;
      }
    }
    if (fit)
      fit->process_results(res);
    consume(nc);
    if (res->Status == res_OK)
      report_ok();
  }
  return 0;
}

void icos_pipe::output(const char *line) {
  int nbline = strlen(line);
  if (logfp) {
    fprintf(logfp, "%s", line);
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

void icos_pipe::setup_pipe() {
  cleanup();
  if (mkfifo(path, 0664) != 0) {
    msg(MSG_ERROR, "%s: mkfifo error %d: %s",
      path, errno, strerror(errno));
  }
  // could use init() here, but it can only be called once
  // without creating a memory leak on buf
  if (is_input) {
    open_pipe();
  }
}

void icos_pipe::open_pipe() {
  fd = open(path, (is_input?O_RDONLY:O_WRONLY)|O_NONBLOCK);
  if (fd < 0) {
    if (is_input) {
      msg(MSG_FATAL, "%s: error %d opening for read: %s",
        path, errno, strerror(errno));
    } else {
      TO.Set(1,0);
      flags = Selector::Sel_Timeout;
    }
    return;
  }
  flags = 
    Selector::Sel_Read |
    Selector::Sel_Write;
}

void icos_pipe::close() {
  if (fd < 0) {
    ::close(fd);
    fd = -1;
    flags = 0;
  }
}

Timeout *icos_pipe::GetTimeout() {
  return &TO;
}

fitd::fitd()
  : 
    PTE(false, 80, "PTE.fifo", "PTE.log"),
    SUM(true, 1024, "ICOSsum.fifo", "ICOSsum.log", this),
    CMD(this),
    TM(0),
    ICOSf(scan_ibase),
    fitting_scannum(0),
    icosfit_status(IFS_Gone),
    icosfit_pid(0)
{
  if (!command_file) {
    TM = new TM_Selectee("icosfitd", &icosfitd, sizeof(icosfitd));
    S.add_child(TM);
  }
  S.add_child(&SUM);
  // S.add_child(&PTE);
  CMD.check_queue();
  
  pthread_getschedparam(pthread_self(), 0, &spawn_sched_param);
  msg(-2, "my_priority = %d", spawn_sched_param.sched_priority);
  --spawn_sched_param.sched_priority;
  // Setup to handle signals
}

fitd::~fitd() {}

void fitd::scan_data(uint32_t scannum, float P, float T,
      const char *PTparams) {
  fitting_scannum = scannum;
  if (icosfit_status == IFS_Gone) {
    launch_icosfit(fitting_scannum);
  }
  if (icosfit_status == IFS_Ready) {
    char PTEline[256];
    snprintf(PTEline, 256, "%u %.2f %.1f %s", fitting_scannum,
      P, T, PTparams);
    PTE.output(PTEline);
    icosfitd.Status = icosfit_status = IFS_Fitting;
  }
}

void fitd::process_results(results *res) {
  switch (res->Status) {
    case res_OK:
      msg(-2, "%u: Successfully fit", res->scannum);
      icosfitd.Status = icosfit_status = IFS_Ready;
      CMD.check_queue();
    case res_synerr:
      msg(3, "Syntax error response from icosfit");
    case res_eof:
      msg(3, "icosfit died");
  }
}

void fitd::launch_icosfit(uint32_t scannum) {
  int linepos = find_line_position(scannum);
  generate_icosfit_file(linepos);
  SUM.setup_pipe();
  PTE.setup_pipe();
  if (spawn_icosfit()) {
    icosfitd.Status = icosfit_status = IFS_Ready;
  }
  PTE.open_pipe();
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
  if (start <= end || start < 0) return 0;
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
  posix_spawnattr_t attr;
  argv[0] = "/usr/local/bin/icosfit";
  argv[1] = icosfit_file_out;
  argv[2] = 0;
  
  if (posix_spawn_file_actions_init(&fact))
    msg(3, "posix_spawn_file_actions_init returned err %d: %s",
      errno, strerror(errno));
  // PTE is not open while launching
  if (posix_spawn_file_actions_addclose(&fact,SUM.fd) ||
      (CMD.fd >= 0 &&
       posix_spawn_file_actions_addclose(&fact,CMD.fd)) ||
      (TM && TM->fd >= 0 &&
        posix_spawn_file_actions_addclose(&fact,CMD.fd))) {
    msg(3, "psfa_addclose returned error %d: %s",
      errno, strerror(errno));
  }

  if (posix_spawnattr_init(&attr) ||
      posix_spawnattr_setschedparam(&attr, &spawn_sched_param)) {
    msg(3, "spawnattr error %d: %s", errno, strerror(errno));
  }
  
  if (posix_spawn(&pid, argv[0], &fact, &attr, (char*const*)argv, 0) < 0) {
    msg(2, "spawn returned error %d: %s", errno, strerror(errno));
    rv = 0;
  }

  if (posix_spawn_file_actions_destroy(&fact))
    msg(2, "posix_spawn_file_actions_destroy returned err %d: %s",
      errno, strerror(errno));
  if (posix_spawnattr_destroy(&attr))
    msg(2, "posix_spawnattr_destroy returned err %d: %s",
      errno, strerror(errno));
  return rv;
}

icos_cmd::icos_cmd(fitd *fit)
    : Ser_Sel(),
      fit(fit),
      PTparams(0),
      PTparams_len(0),
      cur_scannum(0),
      fitting_scannum(0)
{
  if (command_file) {
    ifp = fopen(command_file, "r");
    if (ifp == 0)
      msg(3, "Unable to open command_file %s", command_file);
    fd = fileno(ifp);
    init(0, 0, 300);
  } else {
    init(tm_dev_name("cmd/icosfitd"), O_RDONLY, 300);
    fit->add_child(this);
  }
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
  if (fillbuf()) return 1;
  return protocol_input();
}

int icos_cmd::protocol_input() {
  cp = 0;
  if (cp < nc && buf[cp] == 'S') {
    if (not_str("S:") ||
        not_uint32(cur_scannum) || not_str(",") ||
        not_float(P) || not_str(",") ||
        not_float(T) || not_str("\n")) {
      if (cp < nc)
        report_err("Invalid 'S' command");
      consume(nc);
      return 0;
    }
    if (cur_scannum != fitting_scannum &&
        icosfitd.Status != IFS_Fitting) {
      fit->scan_data(cur_scannum, P, T, PTparams);
      fitting_scannum = cur_scannum;
    }
    consume(nc);
    report_ok();
    return 0;
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
        report_ok();
        consume(++cp);
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
  report_err("Invalid command syntax");
  consume(nc);
  return 0;
}

void icos_cmd::check_queue() {
  // Read commands from the input file a line at a time
  // Stop once a scan has been sent to fitd
  if (!ifp) return;
  if (cur_scannum != fitting_scannum &&
      icosfitd.Status != IFS_Fitting) {
    fit->scan_data(cur_scannum, P, T, PTparams);
    fitting_scannum = cur_scannum;
  } else {
    while (icosfitd.Status != IFS_Fitting) {
      if (fgets((char*)buf, bufsize, ifp)) {
        nc = strlen((const char*)buf);
        protocol_input();
      } else {
        fclose(ifp);
        ifp = 0;
        fd = -1;
        break;
      }
    }
  }
}

icosfitd_t icosfitd;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (!icosfit_file_in)
    msg(3, "Must specify input icosfit configuration file");
  if (!icosfit_file_out)
    icosfit_file_out = "icosfit.RT";

  { fitd fit;
    nl_error(0, "Starting: v1.0");
    fit.event_loop();
  }
  nl_error(0, "Terminating");
}
