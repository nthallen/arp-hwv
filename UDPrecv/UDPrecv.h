#ifndef UDPRECV_H_INCLUDED
#define UDPRECV_H_INCLUDED

class UDPrecv {
  public:
    UDPrecv(const char *host, const char *port);
    ~UDPrecv();
    bool receive();
    const char *data();
  private:
    int fd;
    int n_eagain;
    int n_eintr;
    static const int bufsize = 500;
    char buf[bufsize];
};

#endif
