#tmcbase = /usr/local/share/huarp/freemem.tmc
tmcbase = base.tmc
tmcbase = idx64.tmc
tmcbase = ssp.tmc
tmcbase = qcli.tmc
tmcbase = waves.tmc
tmcbase = T30K75KU.tmc
tmcbase = T10K75KU.tmc
tmcbase = ptrhm.cc
tmcbase = vl_temp.tmc
tmcbase = pwrmon.tmc
#tmcbase = /usr/local/share/huarp/cpu_usage.tmc
#tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = dacsmread.tmc
tmcbase = IWG1.tmc

#cmdbase = /usr/local/share/huarp/root.cmd
#cmdbase = /usr/local/share/huarp/getcon.cmd
cmdbase = /usr/local/share/huarp/idx64.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = idx64drv.cmd 
cmdbase = dccc.cmd
cmdbase = qcli.cmd
cmdbase = ssp.cmd
cmdbase = ai.cmd ao.cmd
cmdbase = soldrv.cmd
cmdbase = waves.cmd
cmdbase = fail.cmd

colbase = ai_init.tmc
colbase = ptrh_chk.tmc
colbase = cnt_init.tmc
colbase = idx64col.tmc
colbase = sspcol.tmc
colbase = vl_temp_col.tmc
colbase = ptrhm_col.cc
#colbase = /usr/local/share/huarp/freemem_col.tmc
colbase = /usr/local/share/huarp/DACS_ID.tmc
#colbase = /usr/local/share/huarp/cpu_usage_col.tmc
#colbase = /usr/local/share/huarp/tmdf_col.tmc
colbase = dacsmread_col.tmc
colbase = IWG1_col.tmc

swsbase = HWV.sws

genuibase = HWV.genui
extbase = ptrh_conv.tmc IRVf.tmc icosfitd_conv.tmc

Module TMbase Panel=HK:
Module icosfitd Panel=HHH: COADD=coadd

SCRIPT = interact
SCRIPT = runfile.FF
SCRIPT = runfile_cal
SCRIPT = dccc.dccc
SCRIPT = idx64.idx64
SCRIPT = hwv_analysis
SRCDIST = waves.qcli waves.m
DISTRIB = waves.out A.sft
DISTRIB = ../IWG1/IWG1
SRC = ptrhm.h
SRC = dacsmread.txt

IGNORE = Makefile
OBJ = waves.cmd waves.out waves.tmc waves.m waves.log
OBJ = address.h
OBJ = dacsmread.tmc dacsmread_col.tmc

TGTDIR = $(TGTNODE)/home/hwv

HWVcol : -lsubbus
HWVsrvr : -lsubbus

HWVdisp : qclibits.tmc sspflags.tmc icosfitd_conv.tmc \
  idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc \
  HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc LyAmr/LyAmrAvg.cc \
  SSPrtg.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl \
  /usr/local/share/oui/cic.oui IWG1.tbl

lydisp : digio.tmc \
  HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc LyAmr/LyAmrAvg.cc \
  icosfitd_conv.tmc lyalpha.tbl
lyamrudpext : HWVmr2.tmc icosfitd_conv.tmc LyAmr/LyAmrSample.cc \
  LyAmr/Circular.cc LyAmr/LyAmrAvg.cc LyAmr/UDP.cc UDP.tmc -lsocket

HWValgo : ptrh_conv.tmc IRVf.tmc HWV.tma HWV.sws icosfitd.tma
HWVcalalgo : ptrh_conv.tmc IRVf.tmc HWVcal.tma HWV.sws

doit : HWV.doit
caldoit : HWVcal.doit
lydoit : ly.doit
A.sft : A.sol
B.sft : B.sol
C.sft : C.sol

# hwvengext : ptrh_conv.tmc IRVf.tmc hwveng.cdf
hwvrawext : ptrh_conv.tmc hwvraw.cdf
hwvext : hwv.cdf
hhhext : hhh.cdf
# PText : PT.cdf
lyamrext : HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc \
           LyAmr/LyAmrAvg.cc lyamr.cdf HWVmr2.oui
%%
COLFLAGS=-Haddress.h
CXXFLAGS=-g
CPPFLAGS+=-I ../IWG1
address.h : HWVcol.cc
HWVsrvr.o : address.h
#hwveng.cdf : genui.txt
#	genui -d ../eng -c genui.txt
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
dacsmread.tmc dacsmread_col.tmc : dacsmread.txt
	./dacsmread.pl dacsmread
../IWG1/IWG1 :
	cd ../IWG1 && make
