/* swstat.h */
#ifndef SWSTAT_H_INCLUDED
#define SWSTAT_H_INCLUDED

typedef struct {
  unsigned short SWStat;
} __attribute__((packed)) swstat_t;
extern swstat_t SWData;

#define SWS_OK 0
#define SWS_TAKEOFF 1
#define SWS_CLIMB 2
#define SWS_DESCEND 3
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
