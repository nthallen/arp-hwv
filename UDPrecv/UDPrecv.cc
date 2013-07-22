#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "UDPrecv.h"
#include "oui.h"
#include "nortlib.h"

const char *host = 0;
const char *port = "5100";

int main(int argc, char **argv) {
  //oui_init_options(argc, argv);
  UDPrecv R(host, port);
  for (;;) {
    if (R.receive())
      printf("%s", R.data());
  }
  return 0;
}

UDPrecv::UDPrecv(const char *host, const char *port) {
  struct addrinfo hints,*results, *p;
  int err;

  if (port == 0)
    nl_error( 3, "Invalid port in UserPkts_UDP: 0" );

  n_eintr = n_eagain = 0;
  memset(&hints, 0, sizeof(hints));	
  hints.ai_family = AF_INET;		// Specify IPv4, not v6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
    
  err = getaddrinfo(host, 
                    port,
                    &hints,
                    &results);
  if (err)
    nl_error( 3, "UDPrecv: getaddrinfo error: %s",
          gai_strerror(err) );
  for(p=results; p!= NULL; p=p->ai_next) {
    fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0)
      nl_error( 2, "UDPrecv: socket error: %s", strerror(errno) );
    else if ( bind(fd, p->ai_addr, p->ai_addrlen) < 0 )
      nl_error( 2, "UDPrecv: bind error: %s", strerror(errno) );
    else break;
  }
  if (fd < 0)
    nl_error(3, "Unable to bind UDP socket");
}

UDPrecv::~UDPrecv() {
  printf("n_eagain = %d\nn_eintr = %d\n", n_eagain, n_eintr);
  close(fd);
}

bool UDPrecv::receive() {
  struct sockaddr_storage from;
  socklen_t fromlen = sizeof(from);
  int rv = recvfrom(fd, &buf[0], bufsize - 1, 0,
              (struct sockaddr*)&from, &fromlen);
	
  if (rv == -1) {
    if ( errno == EWOULDBLOCK ) {
      ++n_eagain;
    } else if (errno == EINTR) {
      ++n_eintr;
    } else {
      nl_error( 3, "UDPrecv::receive(): recvfrom error: %s",
                strerror(errno));
    }
    return false;
  }
  if (rv >= bufsize-1) {
    nl_error(1, "Buffer overfull");
    rv = bufsize-1;
  }
  buf[rv] = '\0';
  return true;
}

const char *UDPrecv::data() {
  return buf;
}
