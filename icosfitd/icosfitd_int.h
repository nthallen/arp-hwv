#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED

#include <stdio.h>
#include <fcntl.h>
#include "icosfitd.h"
#include "SerSelector.h"

class fitd;

class icos_pipe : public Ser_Sel {
  public:
    icos_pipe(bool input, int bufsize,
      const char *path, const char *logfile,
      fitd *fit = 0);
    ~icos_pipe();
    int ProcessData(int flag);
    int output(const char *line);
  protected:
    void cleanup();
    void setup_pipe();
    void close();
    bool is_input;
    const char *path;
    File *logfp;
    fitd *fit;
};

class fitd {
  public:
    fitd(Selector *S);
    ~fitd();
    /**
     * @param scannum The current scan number
     * @param P Cell pressure in torr
     * @param T Cell temperature in Kelvin
     */
    void scan_data(int scannum, float P, float T,
      const char *PTparams);
    void results(const char *res);
  protected:
  private:
    /**
     * spawn()s icosfit with the name of the config
     * file as its only argument. Redirects stdin
     * and stderr to log files.
     */
    void launch_icosfit();
    Selector *S;
    icos_pipe PTE(false, 80, "PTE.fifo", "PTE.log");
    icos_pipe SUM(true, 1024, "ICOSsum.fifo", "ICOSsum.log", this);
    icos_cmd CMD(this);
    TM_Selectee TM("icosfitd", &icosfitd, sizeof(icosfitd));
    uint32_t fitting_scannum;
    uint32_t cur_scannum;
    double cur_P;
    double cur_T;
    FILE *PTEfp;
    FILE *SUMfp;
    icosfitd_status icosfit_status;
    int icosfit_pid;
};

class icos_cmd : public Cmd_Selectee {
  public:
    icos_cmd(fitd *fit);
    int ProcessData(int flag);
  private:
    fitd *fit;
    char *PTparams;
    int PTparams_len;
};

extern void set_icosfit_file(const char *path);
extern bool log_icossum;

#endif
