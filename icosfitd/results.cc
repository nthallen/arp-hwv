/* results.cc */
#include <stdlib.h>
#include <ctype.h>
#include "icosfitd_int.h"
#include "msg.h"

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
  if (n_Vals > MAX_RESULT_VALS)
    msg(3, "More columns specified than arbitrary limit MAX_RESULT_VALS");
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
}
