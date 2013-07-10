#ifndef LYAMR_H_INCLUDED
#define LYAMR_H_INCLUDED

#include <vector>
#include <stdio.h>

class LyAmrSample {
  public:
    LyAmrSample();
    LyAmrSample(double t, double C, double U, double T, double P);
    void clear();
    void set(double t, double C, double U, double T, double P);
    void add(LyAmrSample*);
    void average(LyAmrSample &dest);
    unsigned N();
    double t, C, U, T, P;
  private:
    unsigned NS;
};

class Circular {
  public:
    Circular();
    bool reinit(unsigned size); // calls resize to grow, sets max_size to shrink
    // Returns true if not empty
    LyAmrSample *front();
    bool pop_front(); /** @return true if empty before pop */
    bool push_back(LyAmrSample S); /** @return true if full before push */
    bool full();
    bool empty();
  private:
    std::vector<LyAmrSample> data;
    int max_size; /** The size of the circular buffer. <= data.size() */
    int cur_size; /** The current number of points in the buffer. <= max_size */
    int head; /** Index of the first element */
};

class LyAmrAvg {
  public:
    LyAmrAvg(unsigned fg_pre_ct, unsigned fg_post_ct, unsigned fg_maxN_ct,
              unsigned bg_pre_ct, unsigned bg_post_ct, unsigned bg_maxN_ct);
    ~LyAmrAvg();
    int Process(bool isfg_raw, LyAmrSample S);
    // void averages(double &PMTA, double &UVA1, double &T, double &P);
    bool request_report(const char *filename);
    LyAmrSample fg, bg;
  private:
    enum LyAmrCategory { prefg_cat, foreground_cat, background_cat, transition_cat };
    enum LyAmrState { prefg, prebg, prefgcount, foreground, prebgcount, background };
    void report(double t, LyAmrCategory cat);
    void fg_init();
    void bg_init();
    LyAmrState State;
    unsigned fgpre, fgpost, fg_maxN;
    unsigned bgpre, bgpost, bg_maxN;
    int pre_count;
    Circular PostQ;
    LyAmrSample average;
    FILE *report_fp;
};

#endif
