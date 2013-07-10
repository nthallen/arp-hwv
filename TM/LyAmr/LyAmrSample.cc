#include "LyAmr.h"

LyAmrSample::LyAmrSample() {
  clear();
}

LyAmrSample::LyAmrSample(double t, double C, double U, double T, double P) {
  set(t, C, U, T, P);
}

void LyAmrSample::clear() {
  NS = 0;
  t = C = U = T = P = 0.;
}

void LyAmrSample::set(double t_in, double C_in, double U_in, double T_in, double P_in) {
  NS = 1;
  t = t_in;
  C = C_in;
  U = U_in;
  T = T_in;
  P = P_in;
}

void LyAmrSample::add(LyAmrSample*SP) {
  t += SP->t;
  C += SP->C;
  U += SP->U;
  T += SP->T;
  P += SP->P;
  ++NS;
}

void LyAmrSample::average(LyAmrSample &dest) {
  if (NS > 0) {
    dest.t = t/NS;
    dest.C = C/NS;
    dest.U = U/NS;
    dest.T = T/NS;
    dest.P = P/NS;
  }
  clear();
}

unsigned LyAmrSample::N() {
  return NS;
}
