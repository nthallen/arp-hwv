#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED

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
  protected:
  private:
    /**
     * spawn()s icosfit with the name of the config
     * file as its only argument. Redirects stdin
     * and stderr to log files.
     */
    void launch_icosfit();
    
    
    uint16_t fitting_scannum;
    uint16_t cur_scannum;
    double cur_P;
    double cur_T;
};

class icos_cmd : public Cmd_Selectee {
  public:
    icos_cmd(fitd *fit);
    int ProcessData(int flag);
  private:
    fitd *fit;
};

#endif
