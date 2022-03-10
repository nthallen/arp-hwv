#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdint.h>
typedef uint32_t icos_hdr_t;

#define DOUBLE_PRECISION
#ifdef DOUBLE_PRECISION
typedef double ICOS_Float;
#define RESIZE_INPUT 1
#define FLOAT_STYLE "D"
#define FMT_E "le"
#define FMT_F "lf"
#define FMT_G "lg"
#else
typedef float ICOS_Float;
#define RESIZE_INPUT 0
#define FLOAT_STYLE "F"
#define FMT_E "e"
#define FMT_F "f"
#define FMT_G "g"
#endif

#define MLBASE 1

// This is a placeholder in case we end up compiling on
// a BIG_ENDIAN architecture. The default is LITTLE_ENDIAN.
#define fread_swap32 fread

#endif

