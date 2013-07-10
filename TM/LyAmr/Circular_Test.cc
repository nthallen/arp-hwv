#include "CppUTest/TestHarness.h"
#include "LyAmr.h"
#include "nortlib.h"

// Need to make the Resize test modular so I can run it at multiple sizes

TEST_GROUP(Circular) {
  Circular CB;

  void setup() {
    CHECK(CB.empty());
  }
  
  void exercise_circ(int csize) {
    LyAmrSample S, I(1, 1, 1, 1, 1), *SP;
    int i;
    
    CHECK(CB.empty());
    CHECK(!CB.reinit(csize));
    CHECK(CB.empty());
    CHECK(!CB.full());
    CB.push_back(S);
    CHECK(!CB.empty());
    CHECK(!CB.full());
    SP = CB.front();
    check_equal(SP, 0., 0., 0., 0., 0., 0.);
    // Now fill it full.
    for (i = 1; i < csize; ++i) {
      S.add(&I);
      CHECK(!CB.push_back(S));
    }
    CHECK(!CB.empty());
    CHECK(CB.full());
    // Check that front is still the starting value
    SP = CB.front();
    check_equal(SP, 0., 0., 0., 0., 0., 0.);
    CHECK(!CB.pop_front());
    SP = CB.front();
    check_equal(SP, 1., 1., 1., 1., 1., 1e-6);
    CHECK(!CB.empty());
    CHECK(!CB.full());
    S.add(&I);
    CHECK(!CB.push_back(S));
    CHECK(CB.full());
    for (i = 0; i < csize; ++i) {
      CHECK(!CB.empty());
      CHECK(!CB.pop_front());
      CHECK(!CB.full());
    }
    CHECK(CB.empty());
  }

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

TEST(Circular, Resize) {
  CHECK(CB.full());
  exercise_circ(5);
  exercise_circ(10);
  exercise_circ(3);
}

TEST(Circular, Overflow) {
  int i, resp;
  LyAmrSample S;
  CB.reinit(5);
  for (i = 0; i < 5; ++i)
    CHECK(!CB.push_back(S));
  resp = set_response(NLRSP_QUIET);
  CHECK(CB.push_back(S));
  set_response(resp);
}

TEST(Circular, Underflow) {
  int resp = set_response(NLRSP_QUIET);
  LyAmrSample *SP;
  CHECK(CB.pop_front());
  SP = CB.front();
  POINTERS_EQUAL(0, SP);
  set_response(resp);
}
