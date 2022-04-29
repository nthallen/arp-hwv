#ifndef SPT_H_INCLUDED
#define SPT_H_INCLUDED

#include <stdint.h>

typedef struct {
  uint32_t ScanNum;
  float CellP;
  float Tavg;
} SPT_t;

extern SPT_t SPT[];

#endif

