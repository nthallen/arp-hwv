#ifndef ICOSFITD_INT_H_INCLUDED
#define ICOSFITD_INT_H_INCLUDED

#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <pthread.h>
#include "icosfitd.h"
#include "SerSelector.h"
#include "icosfile.h"

class fitd;
class icos_cmd;

class results {
  public:
    results(const char *param_list);
    ~results();
    uint32_t scannum;
    ICOS_Float P;
    ICOS_Float T;
    ICOS_Float *Vals;
    result_status Status;
    int *ValIdxs;
    int n_Vals;
};

class icos_pipe : public Ser_Sel {
  public:
    icos_pipe(bool input, int bufsize,
      const char *path, const char *logfile,
      fitd *fit = 0);
    ~icos_pipe();
    int ProcessData(int flag);
    void output(const char *line);
    void setup_pipe();
    int open_pipe();
    void close();
    Timeout *GetTimeout();
    int logfd();
    bool is_ready;
  protected:
    int protocol_input();
    void cleanup();
    int not_whitespace();
    bool is_input;
    const char *path;
    FILE *logfp;
    fitd *fit;
    results *res;
    Timeout TO;
};

class icos_cmd : public Ser_Sel {
  public:
    icos_cmd(fitd *fit);
    int ProcessData(int flag);
    int protocol_input();
    int check_queue();
  private:
    bool not_uint32(uint32_t &output_val);
    fitd *fit;
    char *PTparams;
    int PTparams_len;
    uint32_t cur_scannum;
    uint32_t fitting_scannum;
    float P, T;
    FILE *ifp;
};

class fitd {
  public:
    fitd();
    ~fitd();
    inline void add_child(Selectee *P) { S.add_child(P); }
    inline void event_loop() { S.event_loop(); }
    inline int check_queue() { return CMD.check_queue(); }
    /**
     * @param scannum The current scan number
     * @param P Cell pressure in torr
     * @param T Cell temperature in Kelvin
     * @return non-zero to exit the event_loop
     */
    int scan_data(uint32_t scannum, float P, float T,
      const char *PTparams);
    int process_results(results *res);
    int PTE_ready();
  protected:
  private:
    /**
     * spawn()s icosfit with the name of the config
     * file as its only argument. Redirects stdin
     * and stderr to log files.
     */
    int launch_icosfit(uint32_t scannum);
    int find_line_position(uint32_t scannum);
    void generate_icosfit_file(int linepos);
    /**
     * @return non-zero on success
     */
    int spawn_icosfit();
    Selector S;
    icos_pipe PTE;
    icos_pipe SUM;
    icos_cmd CMD;
    TM_Selectee *TM;
    ICOSfile ICOSf;
    uint32_t fitting_scannum;
    icosfitd_status icosfit_status;
    int icosfit_pid;
    struct sched_param spawn_sched_param;
};

/**
 * @param path : icosfit configuration source
 * The icosfit configuration source file is used as a template
 * to write the actual icosfit.RT file, updating the Position=\d+
 * to reflect the line position of the first scan to be fit.
 */
extern void set_icosfit_file(bool isoutput, const char *path);
extern void set_line_search(const char *range);
extern bool log_icossum;
extern const char *scan_ibase;
extern const char *column_list;
extern const char *command_file;
extern FILE *memo_fp, *file_fp;

#endif
