#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "UDP.h"
#include "nortlib.h"
#include "nl_assert.h"

UDPbcast::UDPbcast(const char *broadcast_ip, const char *broadcast_port) {
  ok_status = false;
  ov_status = false;
  bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (bcast_sock == -1) {
    nl_error(nl_response, "Unable to create UDP socket: %s", strerror(errno));
    return;
  }
  int broadcastEnable=1;
  int ret = setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST,
    &broadcastEnable, sizeof(broadcastEnable));
  if (ret == -1) {
    nl_error(nl_response, "setsockopt failed: %s", strerror(errno));
    return;
  }
  struct addrinfo hints, *res;
  hints.ai_flags = AI_NUMERICHOST;
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;
  hints.ai_addrlen = 0;
  hints.ai_canonname = 0;
  hints.ai_addr = 0;
  hints.ai_next = 0;
  if (getaddrinfo(broadcast_ip, broadcast_port, &hints, &res)) {
    nl_error(nl_response, "getaddrinfo failed: %s", strerror(errno));
    return;
  }
  nl_assert(res->ai_next == 0);
  nl_assert(res->ai_addr != 0);
  nl_assert(((unsigned)res->ai_addrlen) <= sizeof(s));
  memcpy(&s, res->ai_addr, res->ai_addrlen);
  addrlen = res->ai_addrlen;
  freeaddrinfo(res);
  ok_status = true;
}

UDPbcast::~UDPbcast() {
  if (bcast_sock != -1) {
    close(bcast_sock);
    bcast_sock = -1;
  }
}

bool UDPbcast::ok() { return ok_status; }

/**
 * @return non-zero on error
 */
int UDPbcast::Broadcast(double utc, unsigned short status, double mr, double HHHmr) {
  char buf[80];
  char lyabuf[80];
  char hhhbuf[80];
  int msglen;
  if (mr > -100) {
    snprintf(lyabuf, 80, "%.2lf", mr);
  } else {
    lyabuf[0] = '\0';
  }
  if (HHHmr > -100) {
    snprintf(hhhbuf, 80, "%.2lf", HHHmr);
  } else {
    hhhbuf[0] = '\0';
  }
  msglen = snprintf(buf, 80, "HWV,%s,%d,%s,%s\r\n",
    ISO8601(utc), status, lyabuf, hhhbuf);
  // if (status == (STATUS_Ready | STATUS_Operating)) {
  //   msglen = snprintf(buf, 80, "HWV,%s,%d,%.2lf\r\n", ISO8601(utc), status, mr);
  // } else {
  //   msglen = snprintf(buf, 80, "HWV,%s,%d,\r\n", ISO8601(utc), status);
  // }
  if (msglen >= 80) {
    if (!ov_status) {
      nl_error(2, "UDP Broadcast buffer overflow");
      ov_status = true;
    }
    return 1; // Don't broadcast a truncated message
  }
  if (ok_status) {
    int nb = sendto(bcast_sock, buf, msglen, 0, (sockaddr*)&s, addrlen);
    if (nb < msglen) {
      nl_error(2, "sendto() expected %d, returned %d", msglen, nb);
      return 1;
    }
  } else {
    return 1;
  }
  return 0;
}

const char *UDPbcast::ISO8601(double utc) {
  // yyyy-mm-ddThh:mm:ss.mmm
  static char buf[24];
  time_t iutc = floor(utc);
  double futc = utc - iutc;
  if (futc >= 1) {
    futc -= 1.0;
    ++iutc;
  } else if (futc < 0) {
    futc += 1.0;
    --iutc;
  }
  struct tm *tms = gmtime(&iutc);
  snprintf(buf, 24, "%4d-%02d-%02dT%02d:%02d:%06.3lf",
    tms->tm_year + 1900,
    tms->tm_mon + 1,
    tms->tm_mday,
    tms->tm_hour,
    tms->tm_min,
    tms->tm_sec + futc);
  return buf;
}
