CPPUTEST_HOME = /usr/local
CPPFLAGS += -I$(CPPUTEST_HOME)/include
LDFLAGS = -L$(CPPUTEST_HOME)/lib
CXXFLAGS = -Wall -g -O0
LDLIBS = -lnort -lCppUTest -lstdc++

.PHONY : all test clean

all : LyAmr_Test UDP_Test All_Test
test : all
	./LyAmr_Test -v
	./UDP_Test -v
clean :
	rm -f *.o LyAmr_Test output.txt averages.txt UDP_Test All_Test

LYAMR_OBJ = LyAmrSample.o LyAmrSample_Test.o
LYAMR_OBJ += Circular.o Circular_Test.o
LYAMR_OBJ += LyAmrAvg.o LyAmrAvg_Test.o
LyAmr_Test : AllTests.o $(LYAMR_OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o LyAmr_Test AllTests.o $(LYAMR_OBJ) $(LDLIBS)

UDP_OBJ = UDP.o UDP_Test.o
UDP_Test : AllTests.o $(UDP_OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o UDP_Test AllTests.o $(UDP_OBJ) $(LDLIBS)

All_Test : AllTests.o $(LYAMR_OBJ) $(UDP_OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o All_Test AllTests.o $(LYAMR_OBJ) $(UDP_OBJ) $(LDLIBS)
