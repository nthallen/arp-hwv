tmcbase = base.tmc
tmcbase = idx64.tmc
tmcbase = swstat.tmc
#tmcbase = ptrh.tmc
tmcbase = ssp.tmc
tmcbase = qcli.tmc
tmcbase = waves.tmc
tmcbase = T30K75KU.tmc
tmcbase = T10K75KU.tmc
tmcbase = ptrh.cc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = /usr/local/share/huarp/idx64.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = idx64drv.cmd 
cmdbase = dccc.cmd
cmdbase = qcli.cmd
cmdbase = ssp.cmd
cmdbase = ai.cmd ao.cmd
cmdbase = soldrv.cmd
cmdbase = swstat.cmd
cmdbase = waves.cmd

SCRIPT = interact
SCRIPT = dccc.dccc
SCRIPT = idx64.idx64
SRCDIST = waves.qcli waves.m
DISTRIB = waves.out A.sft
SRC = ptrh.h

OBJ = waves.cmd waves.out waves.tmc waves.m waves.log
OBJ = address.h

TGTDIR = $(TGTNODE)/home/hwv

HWVcol : ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc ptrh_col.cc -lsubbus
HWVsrvr : -lsubbus
HWVdisp : /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl /usr/local/share/oui/cic.oui
HWValgo : HWV.tma
lydisp : /usr/local/share/huarp/flttime.tmc digio.tmc lyalpha.tbl
doit : HWV.doit
lydoit : ly.doit
A.sft : A.sol
B.sft : B.sol
C.sft : C.sol

hwvengext : ptrh_conv.tmc hwveng.edf
hwvext : hwv.edf
%%
COLFLAGS=-Haddress.h
CXXFLAGS=-g
address.h : HWVcol.cc
HWVsrvr.o : address.h
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
