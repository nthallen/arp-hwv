#include "CppUTest/TestHarness.h"
#include "UDP.h"

TEST_GROUP(UDPbcastGroup) {
};

TEST(UDPbcastGroup, UDPbcast) {
  UDPbcast UDP("10.245.83.127", "5100");
  CHECK(UDP.ok());
  // date -u +'STRCMP_EQUAL(UDP.ISO8601(%s.000), "%Y-%m-%dT%H:%M:%S.000");'
  STRCMP_EQUAL(UDP.ISO8601(1374259532.000), "2013-07-19T18:45:32.000");
  STRCMP_EQUAL(UDP.ISO8601(1374259532.125), "2013-07-19T18:45:32.125");
  CHECK_EQUAL(UDP.Broadcast(1374259532.000, STATUS_Operating), 0);
  CHECK(UDP.ok());
  CHECK_EQUAL(UDP.Broadcast(1374259533.000, STATUS_Operating|STATUS_Ready, 50.), 0);
  CHECK(UDP.ok());
  CHECK_EQUAL(UDP.Broadcast(1374259534.000,
    STATUS_Operating|STATUS_Ready|STATUS_Calibrating), 0);
  CHECK(UDP.ok());
}
