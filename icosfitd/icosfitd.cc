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

void fitd::scan_data(uint32_t scannum, float P, float T) {
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
    fit->scan_data(scannum, P, T);
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
