#include "CppUTest/TestHarness.h"
#include "LyAmr.h"

TEST_GROUP(LyAmrSampleGroup) {
  void check_equal(const LyAmrSample *SP,
        double t, double C, double U, double T, double P, double tol) {
    CHECK(SP != 0);
    DOUBLES_EQUAL(t, SP->t, tol);
    DOUBLES_EQUAL(C, SP->C, tol);
    DOUBLES_EQUAL(U, SP->U, tol);
    DOUBLES_EQUAL(T, SP->T, tol);
    DOUBLES_EQUAL(P, SP->P, tol);
  }
};

TEST(LyAmrSampleGroup, Construct)
{
  LyAmrSample A;
  LyAmrSample B(1., 2., 3., 4., 5.);
  LyAmrSample C, R;

  check_equal(&A, 0, 0, 0, 0, 0, 0);  
  check_equal(&B, 1, 2, 3, 4, 5, 1e-6);
  LONGS_EQUAL(A.N(), 0);
  LONGS_EQUAL(B.N(), 1);
  A.add(&B);
  check_equal(&A, 1, 2, 3, 4, 5, 1e-6);
  LONGS_EQUAL(A.N(), 1);
  LONGS_EQUAL(B.N(), 1);
  A.add(&B);
  A.add(&C);
  A.average(R);
  check_equal(&R, 2./3, 4./3, 6./3, 8./3, 10./3, 1e-6);
  LONGS_EQUAL(A.N(), 0);
  check_equal(&A, 0, 0, 0, 0, 0, 0);  
}
