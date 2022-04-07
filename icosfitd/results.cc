/* results.cc */
#include <stdlib.h>
#include <ctype.h>
#include "icosfitd_int.h"
#include "msg.h"

bool results::res_toggle = false;
results results::res[2];
int results::n_Vals = -1;
int results::ValIdxs[MAX_ICOSFITD_RESULT_VALS];

results *results::active() {
  return res_toggle ? &res[1] : &res[0];
}

results *results::inactive() {
  return res_toggle ? &res[0] : &res[1];
}

void results::toggle() {
  results *r = active();
  r->pending = false;
  res_toggle = !res_toggle;
  r = active();
  r->update_TM();
}

int results::n_results() {
  if (n_Vals < 0) {
    msg(3, "results::n_results() must follow setup()");
  }
  return n_Vals;
}

results *results::newres() {
  results *r = active();
  if (!r->pending ||
      (!r->final && r->Status != res_Fitting))
    return r;
  int32_t active_scan = r->scannum;
  bool active_final = r->final;
  int active_status = r->Status;
  r = inactive();
  if (!r->pending ||
      (!r->final && r->Status != res_Fitting))
    return r;
  msg(-2, "No res: (%ld,%s,%d) (%ld,%s,%d)",
   active_scan, active_final ? "true" : "false",
   active_status,
   r->scannum, r->final ? "true" : "false",
   r->Status);
  return 0;
}

results::results()
  : scannum(0), P(0), T(0), Status(res_None),
    pending(false), final(false) {
  for (int i = 0; i < MAX_ICOSFITD_RESULT_VALS; ++i) {
    Vals[i] = 0;
  }
}

void results::setup(const char *param_list) {
  n_Vals = 0;
  if (!param_list)
    msg(3, "result column list unspecified");
  const char *s = param_list;
  while (*s) {
    if (isdigit(*s)) {
      ++n_Vals;
      ++s;
      while (isdigit(*s)) ++s;
      if (*s == ',') {
        ++s;
      } else if (*s != '\0') {
        msg(3, "Invalid configuration string: '%s'", param_list);
      }
    } else {
      msg(3, "Invalid character in configuration string");
    }
  }
  if (n_Vals > MAX_ICOSFITD_RESULT_VALS)
    msg(3, "More columns specified than arbitrary limit "
           "MAX_ICOSFITD_RESULT_VALS in icosfitd.h");
  s = param_list;
  int idx = 0;
  while (*s) {
    ValIdxs[idx] = strtoul(s, (char**)&s, 10);
    if (idx > 0 && ValIdxs[idx] <= ValIdxs[idx-1])
      msg(3, "Column indexes must be increasing");
    if (*s) ++s;
    ++idx;
  }
  res[0].reset();
  res[1].reset();
}

void results::reset() {
  scannum = 0;
  P = 0;
  T = 0;
  for (int i = 0; i < n_Vals; ++i) {
    Vals[i] = 0.;
  }
  Status = res_None;
  pending = false;
  final = false;
}

void results::init(uint32_t scannum, ICOS_Float P, ICOS_Float T) {
  this->scannum = scannum;
  this->P = P;
  this->T = T;
  for (int i = 0; i < n_Vals; ++i) {
    Vals[i] = 0.;
  }
  Status = res_Queued;
  pending = true;
  final = false;
  update_TM();
}

void results::update_TM() {
  // This should only be called on the active results
  if (this == active()) {
    icosfitd.FitScanNum = scannum;
    icosfitd.P = P;
    icosfitd.T = T;
    for (int i = 0; i < n_Vals; ++i) {
      icosfitd.Vals[i] = Vals[i];
    }
    icosfitd.FitStatus = Status;
  }
}
