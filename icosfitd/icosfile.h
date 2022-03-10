#ifndef ICOSFILE_H_INCLUDED
#define ICOSFILE_H_INCLUDED
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mlf.h"
#include "f_vector.h"
#include "nortlib.h"

#ifndef REQUIRE_ADDITIONAL_COLUMNS
#define REQUIRE_ADDITIONAL_COLUMNS 0
#endif

class ICOSfile {
  public:
    ICOSfile(const char *fbase /* , const char *obase */);
    int read(unsigned long int fileno);
    FILE *writefp();

    mlf_def_t *mlf;
    // mlf_def_t *omlf;
    FILE *ofp;
    /** Scan data vector */
    f_vector *sdata;
    static const int mindatasize;
};

#endif
