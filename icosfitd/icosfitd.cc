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
#include "icosfitd_int.h"

/**
 * These paths need to match between the icosfit file and the
 * driver. The experimenter needs to know where the icosfit
 * file is stored so it can be updated easily. (It should
 * probably be stored in $TMBINDIR!)
 */
const char *PTE_FIFO_PATH = "PTE.fifo";
const char *ICOSsum_FIFO_PATH = "ICOSsum.fifo";

const char *icosfit_file;
bool log_icossum = false;

void set_icosfit_file(const char *path) {
  if (icosfit_file)
    msg(3, "Only one icosfit file can be specified on the command line");
  icosfit_file = path;
}

icos_pipe::icos_pipe(bool input, int bufsize,
        const char *path, const char *logfile, fitd *fit)
    : Ser_Sel(),
      is_input(input),
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
}

icos_pipe::~icos_pipe() {
  cleanup();
}

int icos_pipe::ProcessData(int flag) {
  if (flag & Selector::Sel_Write) {
    msg(MSG, "Pipe %s ready for output", path);
    flags &= ~Selector::Sel_Write;
  }
  if (flag & Selector::Sel_Read) {
    if (is_input) {
      int onc = nc;
      cp = 0;
      fillbuf();
      if (onc == nc) {
        close();
        msg(MSG, "%s closed on read", path);
      } else {
        if (fit) fit->results(buf);
        if (logfp) {
          fprintf(logfp, "%s", buf);
        }
      }
      consume(nc);
      report_ok();
    } else {
      msg(MSG_WARN,"Unexpected input on output pipe %s", path);
      flags &= ~Selector::Sel_Read;
    }
  }
}

int output(const char *line) {
  int nbline = strlen(line);
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

void setup_pipe() {
  cleanup();
  if (mkfifo(path, 0664) != 0) {
    msg(MSG_ERROR, "%s: mkfifo error %d: %s",
      path, errno, strerror(errno));
  }
  // could use init() here, but it can only be called once
  // without creating a memory leak on buf
  fd = open(path, (is_input?O_RDONLY:O_WRONLY)|O_NONBLOCK);
  if (fd < 0) {
    msg(MSG_ERROR, "%s: open error %d: %s",
      path, errno, strerror(errno));
  }
  flags = 
    Selector::Sel_Read |
    Selector::Sel_Write;
}

void close() {
  if (fd < 0) {
    close(fd);
    fd = -1;
    flags = 0;
  }
}

fitd::fitd()
  : Ser_Sel(),
    fitting_scannum(0),
    cur_scannum(0),
    cur_P(0),
    cur_T(0),
    PTEfp(0),
    SUMfp(0)
{
  setup_fifo(PTE_FIFO_PATH);
  setup_fifo(ICOSsum_FIFO_PATH);
  init(ICOSsum_FIFO, O_READ, 1024);
  // Setup to handle signals
  // Open PTE_FIFO_PATH for output
  PTEfp = fopen(PTE_FIFO_PATH, "w");
  if (log_icossum) {
    SUMfp = fopen("ICOSsum.log", "a");
  }
  posix_spawn("icosfit", icosfit_file);
}

void fitd::setup_fifo(const char *path) {
  mkfifo(path, 0664);
}

void fitd::cleanup() {
  if (PTEfp) {
    fclose(PTEfp);
    PTEfp = 0;
  }
  if (SUMfp) {
    fclose(SUMfp);
    SUMfp = 0;
  }
  close();
  // wait for icosfit to terminate and/or send it a signal
  unline(PTE_FIFO_PATH);
  unlink(ICOSsum_FIFO_PATH);
}

void fitd::scan_data(uint32_t scannum, float P, float T,
      const char *PTparams) {
  
}

int fitd::ProcessData(int flag) {
  cp = 0;
  if (flag & Selector::Sel_Read) {
    if (fillbuf()) return 1;
    // Handle read data from ICOSsum.fifo
    consume(nc);
    report_ok();
    return 0;
  }
  if (flag & Selector::Sel_Timeout) {
    // Do we have a timeout on fitting? Perhaps to complain if
    // icosfit dies without a signal.
    // Are we shutting down? Do we need to signal icosfit?
    TO.Clear();
  }
}


icos_cmd::icos_cmd(fitd *fit)
    : Cmd_Selectee("cmd/icosfitd", 300),
      fit(fit),
      PTparams(0),
      PTparams_len(0)
{}

bool icos_cmd::not_uint32(uint32_t &output_val) {
  uint32_t val = 0;
  if (isdigit(buf[cp])) {
    while (isdigit(buf[cp])) {
      val = val*10 + buf[cp++] - '0';
    }
  } else {
    if (cp < nc)
      report_err("%s: not_uint32: no digits at col %d", iname, cp);
    return true;
  }
  output_val = val;
  return false;
}

int icos_cmd::ProcessData(int flag) {
  if (fillbuf()) return 1;
  cp = 0;
  uint32_t scannum;
  float P, T;
  if (cp < nc && buf[cp] == 'S') {
    if (not_str("S:") ||
        not_uint32(scannum) || not_str(",") ||
        not_float(P) || not_str(",") ||
        not_float(T) || not_str("\n")) {
      if (cp < nc)
        report_err("Invalid 'S' command");
      consume(nc);
      return 0;
    }
    fit->scan_data(scannum, P, T, PTparams);
    consume(nc);
    report_ok();
    return false;
  }
  if (cp < nc && buf[cp] == 'P') {
    if (not_str("P:")) {
      if (cp < nc)
        report_err("Invalid 'P' command");
      consume(nc);
      return 0;
    }
    for (int endp = cp; endp < nc; ++endp) {
      if (buf[endp] == '\n') {
        int PT_len = endp - cp;
        if (PT_len >= PTparams_len) {
          if (PTparams) {
            nl_free_memory(PTparams);
          }
          PTparams = (char *)new_memory(PT_len+1);
          PTparams_len = PT_len+1;
        }
        strncpy(PTparams, buf[2], PT_len);
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
    return true;
  }
  report_err("Invalid command syntax");
  consume(nc);
  return false;
}

icosfitd_t icosfitd;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
  
    TM_Selectee TM("icosfitd", &icosfitd, sizeof(icosfitd));
    S.add_child(&TM);
    
    fitd fit();
    S.add_child(&fit);
    
    icos_cmd CS(&fit);
    S.add_child(&CS);

    nl_error(0, "Starting: v1.0");
    S.event_loop();
  }
  nl_error(0, "Terminating");
}
