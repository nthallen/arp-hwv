LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LIBS=-lsocket -ltmpp -ltm -lnort

SRC = icosfitd.cc icosfile.cc f_vector.cc results.cc
OBJ = ${addsuffix .o, ${basename $(SRC) } } icosfitdoui.o
TGT = icosfitd

.PHONY : all clean

all : $(TGT)

icosfitd : $(OBJ)
	$(LINK.cc) -o icosfitd $(OBJ) $(LIBS)
	usemsg icosfitd icosfitdoui.cc
icosfitdoui.cc : icosfitd.oui
	oui -o icosfitdoui.cc icosfitd.oui
icosfitd.o : icosfitd.cc icosfitd.h icosfitd_int.h

clean :
	rm -f *.o icosfitdoui.cc icosfitd
