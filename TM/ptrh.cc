#include "ptrh.h"

ptrh::ptrh( const char *id_in, USHRT base, USHRT C1, USHRT C2,
	    USHRT C3, USHRT C4, USHRT C5, USHRT C6) {
  id = id_in;
  base_addr = base;
  C[0] = C1;
  C[1] = C2;
  C[2] = C3;
  C[3] = C4;
  C[4] = C5;
  C[5] = C6;
  C1d = C1*65536.;
  C2d = C2*131072.;
  C3d = C3/128.;
  C4d = C4/64.;
  C5d = (((uint32_t)C5)<<8);
  C6d = C6/838860800.;
  Off = Sens = 0.;
  stale = 1;
}

/**
 * @return non-zero if coefficient is different
 */
int ptrh::check_coeff( int i, USHRT C_in) {
  nl_assert( i >= 1 && i <= 6 );
  if ( C_in != C[i-1] ) {
    nl_error(2, "PTRH[%s] C%d = 0x%04X, expected 0x%04X",
      id, i, C_in, C[i-1]);
    return 1;
  }
  return 0;
}

/**
 * @return Temperature in Celcius
 */
double ptrh::SHT21T( USHRT S1 ) {
  return(-46.85 + (175.72/65536.) * S1);
}

/**
 * @return Percent Relative Humidity.
 */
double ptrh::SHT21RH( USHRT S2 ) {
  return(-6. + (125./65536.) * S2);
}

/**
 * @return Temperature in Celcius
 */
double ptrh::MS5607T( USHRT Dta, USHRT Dtb) {
  uint32_t D2;
  int32_t dT;
  D2 = (((uint32_t)Dtb)<<16) + Dta;
  dT = D2 - C5d;
  Off = C2d + C4d * dT;
  Sens = C1d + C3d * dT;
  stale = 0;
  return(20. + C6d * dT);
}

/**
 * @return Pressure in mbar
 */
double ptrh::MS5607P( USHRT Dpa, USHRT Dpb) {
  uint32_t D1;
  if ( stale++ == 1 )
    nl_error(1, "PTRH[%s] Converting P using stale T", id);
  D1 = (((uint32_t)Dpb)<<16) + Dpa;
  return((D1*Sens/2097152. - Off)/3276800.);
}

