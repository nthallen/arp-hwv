tmcbase = base.tmc
genuibase = TMdbg.genui

Module TMbase
Module icosfitd RAW=/home/hwv/raw/junk/220408.1/SSP

SCRIPT = interact

IGNORE = Makefile

TGTDIR = $(TGTNODE)/home/hwv/dbg

TMdbgdisp : icosfitd_conv.tmc TMdbg.tbl
#HWVdisp : qclibits.tmc sspflags.tmc icosfitd_conv.tmc \
#  idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc \
#  HWVmr2.tmc LyAmr/LyAmrSample.cc LyAmr/Circular.cc LyAmr/LyAmrAvg.cc \
#  SSPrtg.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl \
#  /usr/local/share/oui/cic.oui IWG1.tbl

TMdbgalgo : TMdbg.tma SPT.cc

doit : TMdbg.doit
%%
CXXFLAGS=-g
