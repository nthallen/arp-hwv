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
    results();
    void reset();
    void init(uint32_t scannum, ICOS_Float P, ICOS_Float T);
    void reinit(uint32_t scannum, ICOS_Float P, ICOS_Float T);
    void update_TM();
    void finalize();
    uint32_t scannum;
    ICOS_Float P;
    ICOS_Float T;
    ICOS_Float Vals[MAX_ICOSFITD_RESULT_VALS];
    result_status Status;
    enum {res_inactive, res_active, res_pending} state;
    results *next;

    static void setup(const char *param_list);
    /**
     * Where results are currently being stored
     */
    static results *active;
    /**
     * Where results are currently being reported
     */
    static results *pending;
    /**
     * return the next available results object or 0
     */
    static results *newres();
    /**
     * Called when TM data is written to collection
     */
    static void posted();
    /**
     * @return true if scan data is queued but not yet submitted to icosfit
     */
    static inline bool queued() {
      return active && (active->Status == res_Queued);
    }
    static int n_results();
    static int ValIdxs[MAX_ICOSFITD_RESULT_VALS];
    static int n_Vals;
  private:
    static bool res_toggle;
    static results res[2];
};

class icos_pipe : public Ser_Sel {
  public:
    icos_pipe(bool input, int bufsize,
      const char *path, const char *logfile,
      fitd *fit = 0);
    ~icos_pipe();
    int ProcessData(int flag);
    void output(const char *line);
    int setup_pipe();
    int open_pipe();
    Timeout *GetTimeout();
    int logfd();
    void cleanup();
    void set_result(results *r);
    bool is_ready;
  protected:
    int protocol_input();
    void close();
    int not_whitespace();
    bool is_input;
    bool in_the_loop;
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
    int submit();
    bool not_uint32(uint32_t &output_val);
    fitd *fit;
    char *PTparams;
    int PTparams_len;
    uint32_t cur_scannum;
    uint32_t prev_scannum;
    float P, T;
    FILE *ifp;
};

class icos_TM : public TM_Selectee {
  public:
    icos_TM(const char *name, void *data, unsigned short size);
    int ProcessData(int flag);
};

class fitd {
  public:
    fitd();
    ~fitd();
    void add_child(Selectee *P);
      // { S.add_child(P); }
    inline void event_loop() { S.event_loop(); }
    inline int check_queue() { return CMD.check_queue(); }
    inline void kill_icosfit() { PTE.output("GACK!\n"); }
    /**
     * @param r results object
     * @return non-zero to exit the event_loop
     */
    int scan_data(results *r, const char *PTparams);
    int process_results(results *res);
    int PTE_ready();
    int recover();
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
    icos_TM *TM;
    ICOSfile ICOSf;
    uint32_t fitting_scannum;
    uint32_t next_scannum;
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
extern int max_coadd;
extern FILE *memo_fp, *file_fp;

#endif
