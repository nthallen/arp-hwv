LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS=-I /usr/local/include
CXXFLAGS=-Wall -g
LIBS=-ltmpp -ltm -lnort -lsocket
.PHONY : clean all

SRC = uplink.cc uplinkoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } }
TGT = uplink

RCVRSRC = uplink_rcvr.cc uplink_rcvroui.c
RCVROBJ = ${addsuffix .o, ${basename $(RCVRSRC) } }
RCVRTGT = uplink_rcvr

all : $(RCVRTGT)

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) uplinkoui.c

uplink.o : uplink.cc uplink.h

uplinkoui.c : uplink.oui
	oui -o uplinkoui.c uplink.oui

$(RCVRTGT) : $(RCVROBJ)
	$(LINK.cc) -o $(RCVRTGT) $(RCVROBJ) $(LIBS)
	usemsg $(RCVRTGT) uplink_rcvroui.c
uplink_rcvroui.c : uplink_rcvr.oui
	oui -o uplink_rcvroui.c uplink_rcvr.oui

clean :
	rm -f *.o uplinkoui.c uplink uplink_rcvroui.c uplink_rcvr
