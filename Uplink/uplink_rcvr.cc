#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "uplink_rcvr.h"
#include "cmdalgo.h"
#include "nortlib.h"
#include "oui.h"

// const char *uplink_port;
// const char *uplink_addr;
// int uplink_baud = 1200;
int UDP_uplink_port = 26130;

/**
 * @param port path to the serial port
 * @param addr the 2-digit hex address of the MaCaPs port we are using
 * If addr is 0, we are operating in flight mode where each byte received
 * is treated as a software status command. If an address is specified,
 * then we are operating in ground test mode. In this mode, we can directly
 * connect the GSE uplink port to the flight computer's uplink_rcvr port.
 * uplink_rcvr will check the validity of the data from uplink, and then
 * process the command the same as in flight.
 */
UplinkRcvrUDP::UplinkRcvrUDP() :
          Ser_Sel(0, 0, 80) {
  Bind(UDP_uplink_port);
  flags = Selector::Sel_Read;
  flush_input();
}

UplinkRcvrUDP::~UplinkRcvrUDP() {}

void UplinkRcvrUDP::Bind(int port) {
	char service[10];
	struct addrinfo hints,*results, *p;
  int err, ioflags;

	if (port == 0)
    nl_error( 3, "Invalid port in IWG1_UDP: 0" );
	snprintf(service, 10, "%d", port);

	memset(&hints, 0, sizeof(hints));	
	hints.ai_family = AF_UNSPEC;		// don't care IPv4 of v6
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	err = getaddrinfo(NULL, 
						service,
						&hints,
						&results);
	if (err)
    nl_error( 3, "IWG1_UDP::Bind: getaddrinfo error: %s", gai_strerror(err) );
	for(p=results; p!= NULL; p=p->ai_next) {
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (fd < 0)
      nl_error( 2, "IWG1_UPD::Bind: socket error: %s", strerror(errno) );
		else if ( bind(fd, p->ai_addr, p->ai_addrlen) < 0 )
      nl_error( 2, "IWG1_UDP::Bind: bind error: %s", strerror(errno) );
		else break;
	}
  if (fd < 0)
    nl_error(3, "Unable to bind UDP socket");
    
  ioflags = fcntl(fd, F_GETFL, 0);
  if (ioflags != -1)
    ioflags = fcntl(fd, F_SETFL, ioflags | O_NONBLOCK);
  if (ioflags == -1)
    nl_error( 3, "Error setting O_NONBLOCK on UDP socket: %s",
      strerror(errno));
}

/**
 * At the moment, just report anything returned
 * from the CSBF equipment
 */
int UplinkRcvrUDP::ProcessData(int flag) {
  if (fillbuf()) return 1;
  cp = 0;
  int sws_value;
  if (not_str("W:") || not_int(sws_value)) {
    if (cp >= nc)
      report_err("Uplink syntax error");
    consume(nc);
  } else {
    if (sws_value >= 0 && sws_value < 256) {
      report_ok();
      ci_sendfcmd(0, "SWStat Set %d\n", sws_value);
    } else {
      report_err("Uplink SWS value out of range: %d", sws_value);
    }
    consume(nc);
  }
  return 0;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error(0, "Starting V1.0");
  { Selector S;
    UplinkRcvrUDP UDP;
    Cmd_Selectee UC;
    S.add_child(&UC);
    S.add_child(&UDP);
    S.event_loop();
  }
  nl_error(0, "Terminating");
}
