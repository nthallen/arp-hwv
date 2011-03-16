#include "ptrh.h"

void ptrh::check_coeffs() {
  int i, ok = 1;
  for (i = 1; i < 6; ++i) {
    USHRT A, C;
    A = base_addr + 4 + 2*i;
    if (!read_ack(A, &C)) {
      nl_error(2, "PTRH[%s] No acknowledge on addr 0x04X", id, A);
    } else {
      if ( check_coeff(i, C) )
	ok = 0;
    }
  }
  if (ok) nl_error(0, "PTRH[%s] Coefficients checked OK", id );
}
