#ifndef UPLINK_RCVR_H_INCLUDED
#define UPLINK_RCVR_H_INCLUDED

extern int UDP_uplink_port;

#ifdef __cplusplus
#include <SerSelector.h>
#include <termios.h>

class UplinkRcvrUDP : public Ser_Sel {
  public:
    UplinkRcvrUDP();
    ~UplinkRcvrUDP();
    int ProcessData(int flag);
    // Timeout *GetTimeout();
  private:
    void Bind(int port);
    // send_id cmd_id;
    // unsigned short addr;
    // Timeout TO;
};

#endif

#endif
