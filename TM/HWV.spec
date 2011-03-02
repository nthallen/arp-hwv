tmcbase = base.tmc
tmcbase = idx64.tmc
tmcbase = swstat.tmc
#tmcbase = ptrh.tmc
tmcbase = ssp.tmc
tmcbase = qcli.tmc
tmcbase = waves.tmc
tmcbase = T30K75KU.tmc
tmcbase = T10K75KU.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = /usr/local/share/huarp/idx64.cmd
cmdbase = idx64drv.cmd 
cmdbase = dccc.cmd
cmdbase = qcli.cmd
cmdbase = ssp.cmd
cmdbase = ao.cmd
cmdbase = soldrv.cmd
cmdbase = swstat.cmd
cmdbase = waves.cmd

SCRIPT = interact
SCRIPT = dccc.dccc
SCRIPT = idx64.idx64
SRCDIST = waves.qcli waves.m
DISTRIB = waves.out A.sft

OBJ = waves.cmd waves.out waves.tmc waves.m waves.log
OBJ = address.h

TGTDIR = $(TGTNODE)/home/HWV

HWVcol : ai_init.tmc cnt_init.tmc idx64col.tmc sspcol.tmc -lsubbus
HWVsrvr : -lsubbus
HWVdisp : /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl
HWValgo : HWV.tma
lydisp : /usr/local/share/huarp/flttime.tmc digio.tmc lyalpha.tbl
doit : HWV.doit
lydoit : ly.doit
A.sft : A.sol
%%
COLFLAGS=-Haddress.h
CXXFLAGS=-g
address.h : HWVcol.cc
HWVsrvr.o : address.h
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
