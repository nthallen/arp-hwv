tmcbase = /usr/local/share/huarp/freemem.tmc
tmcbase = base.tmc
tmcbase = idx64.tmc
#tmcbase = swstat.tmc
#tmcbase = ptrh.tmc
tmcbase = ssp.tmc
tmcbase = qcli.tmc
tmcbase = waves.tmc
tmcbase = T30K75KU.tmc
tmcbase = T10K75KU.tmc
tmcbase = ptrhm.cc
tmcbase = vl_temp.tmc
tmcbase = pwrmon.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = dacsmread.tmc

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
#cmdbase = swstat.cmd
cmdbase = waves.cmd
cmdbase = fail.cmd

colbase = ai_init.tmc
colbase = ptrh_chk.tmc
colbase = cnt_init.tmc
colbase = idx64col.tmc
colbase = sspcol.tmc
colbase = vl_temp_col.tmc
colbase = ptrhm_col.cc
colbase = /usr/local/share/huarp/freemem_col.tmc
colbase = /usr/local/share/huarp/DACS_ID.tmc
colbase = /usr/local/share/huarp/cpu_usage_col.tmc
colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = dacsmread_col.tmc

swsbase = HWV.sws

SCRIPT = interact
SCRIPT = runfile.FF
SCRIPT = dccc.dccc
SCRIPT = idx64.idx64
SRCDIST = waves.qcli waves.m
DISTRIB = waves.out A.sft
SRC = ptrhm.h
SRC = dacsmread.txt

OBJ = waves.cmd waves.out waves.tmc waves.m waves.log
OBJ = address.h
OBJ = dacsmread.tmc dacsmread_col.tmc

TGTDIR = $(TGTNODE)/home/hwv

HWVcol : -lsubbus
HWVsrvr : -lsubbus

HWVdisp : /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc \
  SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc \
  HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc LyAmr/LyAmrAvg.cc \
  HWV.tbl lyalpha.tbl hk.tbl lab.tbl /usr/local/share/oui/cic.oui

lydisp : /usr/local/share/huarp/flttime.tmc digio.tmc \
         HWVmr.cyc HWVmr2.cyc HWVmr.tmc lyalpha.tbl

HWValgo : ptrh_conv.tmc HWV.tma HWV.sws

doit : HWV.doit
lydoit : ly.doit
A.sft : A.sol
B.sft : B.sol
C.sft : C.sol

hwvengext : ptrh_conv.tmc hwveng.cdf
hwvrawext : ptrh_conv.tmc hwvraw.cdf
hwvext : hwv.cdf
hhhext : hhh.cdf
# PText : PT.cdf
lyamrext : HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc \
           LyAmr/LyAmrAvg.cc lyamr.cdf
%%
COLFLAGS=-Haddress.h
CXXFLAGS=-g
address.h : HWVcol.cc
HWVsrvr.o : address.h
hwveng.cdf : genui.txt
	genui -d ../eng -c genui.txt
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
dacsmread.tmc dacsmread_col.tmc : dacsmread.txt
	./dacsmread.pl dacsmread
