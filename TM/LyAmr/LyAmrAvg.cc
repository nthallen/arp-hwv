/* LyAmr.cc
  Current binning criteria:
    Sample(i) is bg if UVA1(i+j) < 50, -1 <= j <= 1
    Sample(i) is fg if UVA1(i+j) >= 50, -2 <= j <= 2
  This results in the following breakdown:
    77.2% fg
    15.3% bg
     7.5% transition points
  Some further optimization is possible by adjusting the j range depending on
  the magnitude of the transition points.
  
  I need to calculate the following 6 averages:
                  FG   BG
    PMT_A_Counts   X    X
    UVA1_Counts    X    X
    CellT          X
    CellP          X
    
  Various channels can be used for CellT and CellP. These can be selected
  using SWStat values.
  -------------------------------
  In reworking the following, I decided to make the interface less generic.
  In the process, the sense of the 'post' parameters will be opposite in
  sign to what is listed here. Furthermore, pre and post will be limited
  to positive (non-zero) values, so we only require a post queue.
  (Not allowing zero values means the first transition point is always
  discarded, which is a reasonable assumption for this data set.) One
  implication of this assumption is that we only need to evaluate the
  State once for each point.
  ------------------------------
  pre is the offset in samples from the first valid sample to the
    first averaged sample.
  post is the offset in samples from the last valid sample to the
    last averaged sample.
  For pre > 0:
    pre is the number of valid samples that are discarded after valid first comes true
  For pre < 0:
    -pre is the number of averaged points before the first valid point.
    Must queue -pre points, decide their fate on the first valid sample.
  For post < 0:
    -post is the number of valid samples that need to be queued.
    On the first invalid point we can decide the fate of all queued points.
  For post > 0:
    we can include post points after the first invalid point in the average
 */
#include "LyAmr.h"
#include "nortlib.h"
#include "nl_assert.h"
  
LyAmrAvg::LyAmrAvg(unsigned fg_pre_ct, unsigned fg_post_ct, unsigned fg_maxN_ct,
              unsigned bg_pre_ct, unsigned bg_post_ct, unsigned bg_maxN_ct) {
  fgpre = fg_pre_ct;
  fgpost = fg_post_ct;
  fg_maxN = fg_maxN_ct;
  bgpre = bg_pre_ct;
  bgpost = bg_post_ct;
  bg_maxN = bg_maxN_ct;
  State = prefg;
  report_fp = NULL;
}

LyAmrAvg::~LyAmrAvg() {
  // Guarantee that we have a report for each input
  while (!PostQ.empty()) {
    LyAmrSample *SP = PostQ.front();
    report(SP->t, transition_cat);
    PostQ.pop_front();
  }
  if (report_fp) {
    fclose(report_fp);
  }
}

/**
 * @return non-zero when a new foreground average is calculated
 */
int LyAmrAvg::Process(bool isfg_raw, LyAmrSample S) {
  int rv = 0;
  switch (State) {
    case prefg:
      if (isfg_raw) {
        State = prebg;
      }
      report(S.t, prefg_cat);
      break;
    case prebg:
      if (!isfg_raw) {
        pre_count = bgpre-1;
        State = pre_count ? prebgcount : background;
        average.clear();
        PostQ.reinit(bgpost);
      }
      report(S.t, prefg_cat);
      break;
    case prefgcount:
      if (isfg_raw) {
        if (--pre_count == 0) {
          State = foreground;
        }
      } else {
        if (nl_response)
          nl_error(1, "%.3lf: Short foreground cycle", S.t);
        bg_init();
      }
      report(S.t, transition_cat);
      break;
    case foreground:
      if (isfg_raw) {
        if (PostQ.full()) {
          LyAmrSample *SP = PostQ.front();
          average.add(SP);
          report(SP->t, foreground_cat);
          PostQ.pop_front();
          if (fg_maxN > 0 && average.N() >= fg_maxN) {
            average.average(fg);
            rv = 1;
          }
        }
        PostQ.push_back(S);
      } else {
        while (!PostQ.empty()) {
          LyAmrSample *SP = PostQ.front();
          report(SP->t, transition_cat);
          PostQ.pop_front();
        }
        report(S.t, transition_cat);
        if (average.N()) {
          average.average(fg);
          rv = 1;
        }
        bg_init();
      }
      break;
    case prebgcount:
      if (!isfg_raw) {
        if (--pre_count == 0) {
          State = background;
        }
      } else {
        if (nl_response)
          nl_error(1, "%.3lf: Short background cycle", S.t);
        fg_init();
      }
      report(S.t, transition_cat);
      break;
    case background:
      if (!isfg_raw) {
        if (PostQ.full()) {
          LyAmrSample *SP = PostQ.front();
          average.add(SP);
          report(SP->t, background_cat);
          PostQ.pop_front();
          if (bg_maxN > 0 && average.N() >= bg_maxN) {
            average.average(bg);
          }
        }
        PostQ.push_back(S);
      } else {
        while (!PostQ.empty()) {
          LyAmrSample *SP = PostQ.front();
          report(SP->t, transition_cat);
          PostQ.pop_front();
        }
        report(S.t, transition_cat);
        if (average.N()) {
          average.average(bg);
        }
        fg_init();
      }
      break;
    default:
      nl_error(4, "Invalid PreState");
  }
  return rv;
}

void LyAmrAvg::report(double t, LyAmrCategory cat) {
  if (report_fp) {
    fprintf(report_fp, "%.3lf, %d\n", t, cat);
  }
}

void LyAmrAvg::fg_init() {
  pre_count = fgpre - 1;
  State = pre_count ? prefgcount : foreground;
  nl_assert(average.N() == 0);
  PostQ.reinit(fgpost);
}

void LyAmrAvg::bg_init() {
  pre_count = bgpre - 1;
  State = pre_count ? prebgcount : background;
  nl_assert(average.N() == 0);
  PostQ.reinit(bgpost);
}

/**
 * @return true if file cannot be opened.
 */
bool LyAmrAvg::request_report(const char *filename) {
  report_fp = fopen(filename, "w");
  if (report_fp == NULL) {
    if (nl_response)
      nl_error(2, "Unable to open report file '%s'", filename);
    return true;
  }
  return false;
}
