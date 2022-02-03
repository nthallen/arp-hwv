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


fitd::fitd() : Ser_Sel() {
  // Setup PTE FIFO
  mkfifo(PTE_FIFO_PATH, 0664);
  // Setup ICOSsum.dat FIFO
  mkfifo(ICOSsum_FIFO_PATH, 0664);
  // Open log file for append
  fopen("ICOSfit.log", "a");
  
}

void fitd::scan_data(uint32_t scannum, float P, float T) {
}


icos_cmd::icos_cmd(fitd *fit)
    : Cmd_Selectee("cmd/icosfitd", 80),
      fit(fit)
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
