#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "nortlib.h"
#include "oui.h"
#include "IWG1_int.h"

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    IWG1_UDP IWG1;
    Cmd_Selectee CS;
    S.add_child(&IWG1);
    S.add_child(&CS);
    nl_error(0, "Starting: v1.0");
    S.event_loop();
  }
  nl_error(0, "Terminating");
}

IWG1_UDP::IWG1_UDP() : Ser_Sel( 0, 0, 600 ) {
  // Set up TM
  tm_id = Col_send_init( "IWG1", &IWG1, sizeof(IWG1_data_t), 0);
  // Set up UDP listener
  Bind(NULL, "7071");
  flags = Selector::Sel_Read;
  flush_input();
  setenv("TZ", "UTC0", 1); // Force UTC for mktime()
}

int IWG1_UDP::ProcessData(int flag) {
  if (fillbuf()) return 1;
  if (not_str( "IWG1," ) ||
      not_ISO8601(&IWG1.Time) || not_str( ",", 1) ||
      not_nfloat(&IWG1.Lat) || not_str(",", 1) ||
      not_nfloat(&IWG1.Lon) || not_str(",", 1) ||
      not_nfloat(&IWG1.GPS_MSL_Alt) || not_str(",", 1) ||
      not_nfloat(&IWG1.WGS_84_Alt) || not_str(",", 1) ||
      not_nfloat(&IWG1.Press_Alt) || not_str(",", 1) ||
      not_nfloat(&IWG1.Radar_Alt) || not_str(",", 1) ||
      not_nfloat(&IWG1.Grnd_Spd) || not_str(",", 1) ||
      not_nfloat(&IWG1.True_Airspeed) || not_str(",", 1) ||
      not_nfloat(&IWG1.Indicated_Airspeed) || not_str(",", 1) ||
      not_nfloat(&IWG1.Mach_Number) || not_str(",", 1) ||
      not_nfloat(&IWG1.Vert_Velocity) || not_str(",", 1) ||
      not_nfloat(&IWG1.True_Hdg) || not_str(",", 1) ||
      not_nfloat(&IWG1.Track) || not_str(",", 1) ||
      not_nfloat(&IWG1.Drift) || not_str(",", 1) ||
      not_nfloat(&IWG1.Pitch) || not_str(",", 1) ||
      not_nfloat(&IWG1.Roll) || not_str(",", 1) ||
      not_nfloat(&IWG1.Side_slip) || not_str(",", 1) ||
      not_nfloat(&IWG1.Angle_of_Attack) || not_str(",", 1) ||
      not_nfloat(&IWG1.Ambient_Temp) || not_str(",", 1) ||
      not_nfloat(&IWG1.Dew_Point) || not_str(",", 1) ||
      not_nfloat(&IWG1.Total_Temp) || not_str(",", 1) ||
      not_nfloat(&IWG1.Static_Press) || not_str(",", 1) ||
      not_nfloat(&IWG1.Dynamic_Press) || not_str(",", 1) ||
      not_nfloat(&IWG1.Cabin_Press) || not_str(",", 1) ||
      not_nfloat(&IWG1.Wind_Speed) || not_str(",", 1) ||
      not_nfloat(&IWG1.Wind_Dir) || not_str(",", 1) ||
      not_nfloat(&IWG1.Vert_Wind_Spd) || not_str(",", 1) ||
      not_nfloat(&IWG1.Solar_Zenith) || not_str(",", 1) ||
      not_nfloat(&IWG1.Sun_Elev_AC) || not_str(",", 1) ||
      not_nfloat(&IWG1.Sun_Az_Grd) || not_str(",", 1) ||
      not_nfloat(&IWG1.Sun_Az_AC)) {
    if (cp < nc) {
      nc = cp = 0; // syntax error (already reported). Empty
    } // else cp == nc, so it was a partial record. See if we will get more.
    return 0;
  }
  Col_send(tm_id);
  consume(nc);
  return 0;
}

int IWG1_UDP::not_ndigits(int n, int &value) {
  int i = n;
  value = 0;
  while ( i > 0 && cp < nc && isdigit(buf[cp])) {
    value = value*10 + buf[cp++] - '0';
    --i;
  }
  if (i > 0) {
    if (cp < nc)
      report_err("Expected %d digits at column %d", n, cp-i);
    return 1;
  }
  return 0;
}

int IWG1_UDP::not_ISO8601(double *Time) {
  struct tm buft;
  float secs;
  time_t ltime;

  if (not_ndigits(4, buft.tm_year) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mon) ||
      not_str("-",1) ||
      not_ndigits(2, buft.tm_mday) ||
      not_str("T", 1) ||
      not_ndigits(2, buft.tm_hour) ||
      not_str(":",1) ||
      not_ndigits(2, buft.tm_min) ||
      not_str(":",1) ||
      not_float(secs))
    return 1;
  buft.tm_year -= 1900;
  buft.tm_mon -= 1;
  buft.tm_sec = 0;
  ltime = mktime(&buft);
  if (ltime == (time_t)(-1))
    report_err("mktime returned error");
  else *Time = ltime + secs;
  return 0;
}

/**
 * accept a float or return a NaN (99999.)
 * if the next char is a comma or CR
 */
int IWG1_UDP::not_nfloat(float *value) {
  float val;
  while (cp < nc && buf[cp] == ' ') ++cp;
  if (cp >= nc) return 1;
  if (buf[cp] == ',' || buf[cp] == '\r' || buf[cp] == '\n') {
    *value = 99999.;
    return 0;
  }
  if (not_float(val)) return 1;
  *value = val;
  return 0;
}

void IWG1_UDP::Bind(const char *interface, const char *port_str) {
  struct addrinfo hints,*results, *p;
  int err, ioflags, port;

  port = atoi(port_str);
  if (port == 0)
    nl_error( 3, "Invalid port in IWG1_UDP: 0" );

  memset(&hints, 0, sizeof(hints));	
  hints.ai_family = AF_UNSPEC;		// don't care IPv4 of v6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  
  err = getaddrinfo(interface, 
            port_str,
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

int IWG1_UDP::fillbuf() {
  struct sockaddr_storage from;
  socklen_t fromlen = sizeof(from);
  int rv = recvfrom(fd, &buf[nc],	bufsize - nc - 1, 0,
            (struct sockaddr*)&from, &fromlen);
  
  if (rv == -1) {
    if ( errno == EWOULDBLOCK ) {
      ++n_eagain;
    } else if (errno == EINTR) {
      ++n_eintr;
    } else {
      nl_error( 2, "IWG1_UDP::fillbuf: recvfrom error: %s", strerror(errno));
      return 1;
    }
    return 0;
  }
  nc += rv;
  buf[nc] = '\0';
  return 0;
}
