#ifndef ICOSFITD_H_INCLUDED
#define ICOSFITD_H_INCLUDED
#include <stdint.h>

enum icosfitd_status { IFS_Gone, IFS_Ready, IFS_Fitting };

typedef struct {
  uint32_t FitScanNum;
  float FitWVmr;
  uint8_t Status; // Takes icosfitd_status values
} icosfitd_t;

extern icosfitd_t icosfitd;

#endif
