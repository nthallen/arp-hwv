#ifndef UDP_H_INCLUDED
#define UDP_H_INCLUDED
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define STATUS_Ready 1
#define STATUS_Operating 2
#define STATUS_Calibrating 4
#define STATUS_Warning 8
#define STATUS_Invalid 16
#define STATUS_Failed 32

class UDPbcast {
  public:
    UDPbcast(const char *broadcast_ip, const char *broadcast_port);
    int Broadcast(double utc, unsigned short status, double mr = 0.);
    const char *ISO8601(double utc);
    bool ok();
  private:
    int bcast_sock;
    bool ok_status;
    bool ov_status;
    struct sockaddr_in s;
    socklen_t addrlen;
};

#endif
