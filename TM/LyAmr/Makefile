CPPUTEST_HOME = /usr/local
CPPFLAGS += -I$(CPPUTEST_HOME)/include
LDFLAGS = -L$(CPPUTEST_HOME)/lib
CXXFLAGS = -Wall -g -O0
LDLIBS = -lnort -lCppUTest -lstdc++

.PHONY : test clean

test : LyAmr_Test
	./LyAmr_Test -v
clean :
	rm -f *.o LyAmr_Test output.txt averages.txt

LYAMR_OBJ = AllTests.o
LYAMR_OBJ += LyAmrSample.o LyAmrSample_Test.o
LYAMR_OBJ += Circular.o Circular_Test.o
LYAMR_OBJ += LyAmrAvg.o LyAmrAvg_Test.o
LyAmr_Test : $(LYAMR_OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o LyAmr_Test $(LYAMR_OBJ) $(LDLIBS)

UDP_OBJ = AllTests.o UDP.o UDP_Test.o
UDP_Test : $(UDP_OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o UDP_Test $(UDP_OBJ) $(LDLIBS)