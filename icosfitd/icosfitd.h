#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED
#include <stdint.h>
#include "config.h"

enum result_status { res_None, res_Queued, res_Fitting, res_Fit,
                     res_Syntax, res_EOF };
enum icosfitd_status { IFS_Gone, IFS_Standby, IFS_Ready, IFS_Fitting };
#define MAX_ICOSFITD_RESULT_VALS 5

#ifndef N_ICOSFITD_RESULT_VALS
#define N_ICOSFITD_RESULT_VALS MAX_ICOSFITD_RESULT_VALS
#endif

#if N_ICOSFITD_RESULT_VALS > MAX_ICOSFITD_RESULT_VALS
#error N_ICOSFITD_RESULT_VALS exceeds MAX_ICOSFITD_RESULT_VALS
#endif

typedef struct {
  uint32_t FitScanNum;
  ICOS_Float P, T;
  uint16_t FitStatus; // Takes result_status values
  uint16_t Status; // Takes icosfitd_status values
  ICOS_Float Vals[N_ICOSFITD_RESULT_VALS];
} icosfitd_t;

extern icosfitd_t icosfitd;

#endif
