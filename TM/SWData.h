/* SWData.h */
#ifndef SWDATA_H_INCLUDED
#define SWDATA_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  unsigned short SWStat;
} SWData_t;
extern SWData_t SWData;

#define SWS_TAKEOFF 1
#define SWS_LAND 4
#define SWS_DFB_START 10
#define SWS_DFB_STOP 11
#define SWS_DFB_HHH 12
#define SWS_H2O_ENABLE 20
#define SWS_H2O_DISABLE 21
#define SWS_TIME_WARP 253
#define SWS_READFILE 254
#define SWS_SHUTDOWN 255

#endif
