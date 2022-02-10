#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED

#include <stdio.h>
#include <fcntl.h>
#include "icosfitd.h"
#include "SerSelector.h"

class fitd : public Ser_Sel {
  public:
    fitd();
    ~fitd();
    /**
     * @param scannum The current scan number
     * @param P Cell pressure in torr
     * @param T Cell temperature in Kelvin
     */
    void scan_data(int scannum, float P, float T);
    int ProcessData(int flag);
    inline Timeout *GetTimeout() { return &TO; }
  protected:
  private:
    /**
     * spawn()s icosfit with the name of the config
     * file as its only argument. Redirects stdin
     * and stderr to log files.
     */
    void launch_icosfit();
    /**
     * Creates named FIFO at the specified path.
     * Removes any existing file or FIFO beforehand.
     */
    void setup_fifo(const char *path);
    
    Timeout TO;
    uint16_t fitting_scannum;
    uint16_t cur_scannum;
    double cur_P;
    double cur_T;
    FILE *PTEfp;
    FILE *SUMfp;
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
