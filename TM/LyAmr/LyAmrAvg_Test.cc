#include "CppUTest/TestHarness.h"
#include "LyAmr.h"

TEST_GROUP(LyAmrAvgGroup) {
};

TEST(LyAmrAvgGroup, LyAmrAvg) {
  LyAmrAvg A(2, 2, 8, 1, 1, 0);
  FILE *ifp = fopen("input.txt", "r");
  FILE *ofp = fopen("averages.txt", "w");
  int Nfg = 0;
  int Row = 0;

  CHECK(ifp != NULL);
  A.request_report("output.txt");
  for (;;) {
    int ni, isfg_raw, C, U;
    double t, T, P;
    ni = fscanf(ifp, "%lf,%d,%d,%d,%lf,%lf\n",
      &t, &isfg_raw, &C, &U, &T, &P);
    if (ni <= 0) break;
    ++Row;
    LONGS_EQUAL(6, ni);
    if (A.Process(isfg_raw, LyAmrSample(t, C, U, T, P))) {
      ++Nfg;
      fprintf(ofp, "%.3lf,%.1lf,%.1lf,%.3lf,%.1lf,%.1lf\n",
        A.fg.t, A.fg.C, A.fg.U, A.bg.t, A.bg.C, A.bg.U);
    }
  }
  LONGS_EQUAL(146925, Row);
  LONGS_EQUAL(14011, Nfg);
  fclose(ifp);
  fclose(ofp);
}

