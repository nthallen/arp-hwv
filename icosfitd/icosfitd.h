#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED
#include <stdint.h>

enum result_status { res_OK, res_synerr, res_eof }
enum icosfitd_status { IFS_Gone, IFS_Ready, IFS_Fitting };
#define MAX_RESULT_VALS 5

typedef struct {
  uint32_t FitScanNum;
  ICOS_Float P, T;
  uint16_t FitStatus; // Takes result_status values
  uint16_t Status; // Takes icosfitd_status values
  ICOS_Float Vals[MAX_RESULT_VALS];
} icosfitd_t;

extern icosfitd_t icosfitd;

#endif
