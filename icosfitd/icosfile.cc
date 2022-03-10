/* icosfile.cc */
#include "icosfile.h"

const int ICOSfile::mindatasize = 2048;

ICOSfile::ICOSfile( const char *fbase /* const char *obase */) {
  mlf = mlf_init( 3, 60, 0, fbase, "dat", NULL );
  // omlf = mlf_init( 3, 60, 1, obase, "dat", NULL );
  // ofp = 0;
  // Intentionally going with 1-based addressing for this to match
  // Matlab usage.
  sdata = new f_vector(mindatasize, 1);
  // bdata = new f_vector(mindatasize, 1);
  // fdata = new f_vector(100, 0);
}


/**
 * @param fileno Input file index for multi-level-file routines
 * @return 1 on success, 0 if there was an error
 * For ASCII Processing:
 *  fgets() reads in the line including the newline
 *  strtod() updates the endptr (ep) to point to the char
 *  immediately following the converted value. This should
 *  satisfy isspace(*ep) for every successful conversion,
 *  and since strtod swallows whitespace at the beginning,
 *  it should be false for every unsuccessful conversion.
 *
 *  An ASCII file is deemed to have an etalon if there are
 *  two numbers on a line. Clearly it would make sense
 *  to make this determination once per file and avoid
 *  testing each line.
 */
int ICOSfile::read( unsigned long int fileno ) {
  FILE *fp;
  mlf_set_index( mlf, fileno );
  fp = mlf_next_file(mlf);
  if ( fp == 0 ) return 0;
  sdata->clear();
  // bdata->clear();
    icos_hdr_t header[2];
    if ( fread_swap32( header, sizeof(icos_hdr_t), 2, fp ) != 2 ) {
      nl_error( 2, "%s: Error reading header: %s", mlf->fpath,
        strerror(errno) );
      fclose(fp);
      return 0;
    }
    // Support for new SSP file format
    if ((header[0] | 0x10000) == 0x10006 && header[1] > 255) {
      icos_hdr_t data[5];
      if (fread(data, sizeof(icos_hdr_t), 5, fp) != 5) {
        nl_error( 2, "%s: Error reading SSP header: %s", mlf->fpath,
          strerror(errno) );
        fclose(fp);
        return 0;
      }
      header[0] = header[1]>>16;
      header[1] &= 0xFF;
    }
    if ( header[0] <= 0 || header[1] <= 0 || header[1] > 3 ) {
      nl_error( 2, "%s: Invalid header ( %ld, %ld )", mlf->fpath,
        header[0], header[1] );
      fclose(fp);
      return 0;
    }
    sdata->check(header[0]);
    sdata->n_data =
      fread_swap32( sdata->data+sdata->offset, sizeof(float), header[0], fp );
    if ( sdata->n_data != (int)header[0] ) {
      nl_error( 2, "%s: Error reading sdata: %s", mlf->fpath, strerror(errno) );
      fclose(fp);
      return 0;
#if RESIZE_INPUT
    } else {
      float *raw = (float*)(sdata->data+sdata->offset);
      raw = raw - sdata->offset;
      for (int i = sdata->n_data; i > 0; --i) {
        sdata->data[i] = raw[i];
      }
#endif
    }
    
#if REQUIRE_ADDITIONAL_COLUMNS
    if ( GlobalData.ICOSdirFineTuned ) {
      if ( wndata == 0 ) ICOSfile::wndata = new f_vector( header[0]+1, 0 );
      wndata->check(header[0]);
      wndata->n_data =
        fread_swap32( wndata->data+wndata->offset, sizeof(float), header[0], fp );
      if ( sdata->n_data != (int)header[0] ) {
        nl_error( 2, "%s: Error reading etalon/wndata: %s", mlf->fpath, strerror(errno) );
        fclose(fp);
        return 0;
  #if RESIZE_INPUT
      } else {
        float *raw = (float*)(wndata->data+wndata->offset);
        raw = raw - wndata->offset;
        for (int i = wndata->n_data; i > 0; --i) {
          wndata->data[i] = raw[i];
        }
  #endif
      }
    } else if (GlobalData.BaselineInput && header[1] >= 3) {
      // Skip column 2 (etalon)
      if (fseek(fp, header[0] * sizeof(float), SEEK_CUR)) {
        nl_error( 2, "%s: Error skipping edata: %s", mlf->fpath,
          strerror(errno));
        fclose(fp);
        return 0;
      }
    }
    if (GlobalData.BaselineInput && header[1] >= 3) {
      bdata->check(header[0]);
      bdata->n_data =
        fread_swap32( bdata->data+bdata->offset, sizeof(float), header[0], fp );
      if ( bdata->n_data != (int)header[0] ) {
        nl_error( 2, "%s: Error reading bdata: %s", strerror(errno) );
        fclose(fp);
        return 0;
#if RESIZE_INPUT
      } else {
        float *raw = (float*)(bdata->data+bdata->offset);
        raw = raw - bdata->offset;
        for (int i = bdata->n_data+bdata->offset-1; i >= bdata->offset; --i) {
          bdata->data[i] = raw[i];
        }
#endif
      }
    }
#endif // REQUIRE_ADDITIONAL_COLUMNS
  fclose(fp);
  return 1;
}
