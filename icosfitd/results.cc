/* results.cc */
#include <stdlib.h>
#include <ctype.h>
#include "icosfitd_int.h"
#include "msg.h"

bool results::res_toggle = false;
results results::res[2];

results *results::active() {
  return res_toggle ? &res[1] : &res[0];
}

results *results::inactive() {
  return res_toggle ? &res[0] : &res[1];
}

void results::toggle() {
  results *r = active();
  r->reset();
  res_toggle = !res_toggle;
}

results *results::newres() {
  results *r = active();
  if (!r->pending) return r;
  r = inactive();
  if (!r->pending) return r;
  return 0;
}

results::results(const char *param_list) {
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
    msg(3, "More columns specified than arbitrary limit MAX_ICOSFITD_RESULT_VALS in icosfitd.h");
  Vals = (ICOS_Float*)new_memory(n_Vals * sizeof(ICOS_Float));
  ValIdxs = (int *)new_memory(n_Vals * sizeof(int));
  s = param_list;
  int idx = 0;
  while (*s) {
    ValIdxs[idx] = strtoul(s, (char**)&s, 10);
    if (idx > 0 && ValIdxs[idx] <= ValIdxs[idx-1])
      msg(3, "Column indexes must be increasing");
    if (*s) ++s;
    ++idx;
  }
  reset();
}

void results::reset() {
  init(0, 0., 0.);
  Status = res_None;
}

void results::init(uint32_t scannum, ICOS_Float P, ICOS_Float T) {
  this->scannum = scannum;
  this->P = P;
  this->T = T;
  for (int i = 0; i < n_vals; ++i) {
    Vals[i] = 0.;
  }
  Status = res_Queued;
  pending = false;
  final = false;
}

void results::update_TM() {
  // This should only be called on the active results
  icosfitd.FitScanNum = scannum;
  icosfitd.P = P;
  icosfitd.T = T;
  for (int i = 0; i < n_Vals; ++i) {
    icosfitd.Vals[i] = Vals[i];
  }
  icosfitd.Status = Status;
  pending = true;
}
