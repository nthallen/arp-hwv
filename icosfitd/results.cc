/* results.cc */
#include <stdlib.h>
#include <ctype.h>
#include "icosfitd_int.h"
#include "msg.h"

results results::res[2];
results *results::active;
results *results::pending;
int results::n_Vals = -1;
int results::ValIdxs[MAX_ICOSFITD_RESULT_VALS];

int results::n_results() {
  if (n_Vals < 0) {
    msg(3, "results::n_results() must follow setup()");
  }
  return n_Vals;
}

results *results::newres() {
  results *rv = 0;
  if (!active) {
    if (pending) {
      if (pending->next->state == res_inactive)
        rv = pending->next;
    } else {
      if (res[0].state != res_inactive || res[1].state != res_inactive)
        msg(3, "One or more results not inactive despite !pending && !active");
      rv = &res[0];
    }
  }
  return rv;
}

void results::posted() {
  if (pending && pending->state == res_pending) {
    pending->state = res_inactive;
    if (pending->next->state != res_inactive) {
      pending = pending->next;
      pending->update_TM();
    } else {
      pending = 0;
      icosfitd.FitStatus = res_None;
    }
  }
}

results::results()
  : scannum(0), P(0), T(0), Status(res_None),
    state(res_inactive), next(0) {
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
  res[0].next = &res[1];
  res[1].next = &res[0];
  res[0].reset();
  res[1].reset();
}

void results::reset() {
  scannum = 0;
  P = 0;
  T = 0;
  for (int i = 0; i < MAX_ICOSFITD_RESULT_VALS; ++i) {
    Vals[i] = 0.;
  }
  Status = res_None;
  state = res_inactive;
}

void results::init(uint32_t scannum, ICOS_Float P, ICOS_Float T) {
  if (state != res_inactive || active)
    msg(3, "results::init() while !inactive || active");
  this->scannum = scannum;
  this->P = P;
  this->T = T;
  for (int i = 0; i < n_Vals; ++i) {
    Vals[i] = 0.;
  }
  Status = res_Queued;
  state = res_active;
  active = this;
  if (!pending) {
    pending = this;
    update_TM(); // only updates pending
  }
}

void results::reinit(uint32_t scannum, ICOS_Float P, ICOS_Float T) {
  if (Status != res_Queued || state != res_active || this != active)
    msg(3, "results::reinit() while !Queued || active");
  this->scannum = scannum;
  this->P = P;
  this->T = T;
  update_TM(); // only updates if pending
}

void results::update_TM() {
  // This could be a static function and only update the pending object
  if (this == pending) {
    msg(-2, "update_TM() %d, %d, nVals=%d %g %g %g %g %g",
      scannum, Status, n_Vals, Vals[0], Vals[1], Vals[2], Vals[3], Vals[4]);
    icosfitd.FitScanNum = scannum;
    icosfitd.P = P;
    icosfitd.T = T;
    for (int i = 0; i < n_Vals; ++i) {
      icosfitd.Vals[i] = Vals[i];
    }
    icosfitd.FitStatus = Status;
  } else {
    msg(-2, "update_TM(not) %d, %d", scannum, Status);
  }
}

void results::finalize() {
  msg(-2, "finalize() %d, %d", scannum, Status);
  if (state != res_active || this != active)
    msg(3, "results::finalize() when !active");
  state = res_pending;
  active = 0;
  if (!pending) pending = this;
  update_TM();
}
