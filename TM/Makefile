# Makefile Generated Tue Jul 02 15:01:02 EDT 2019
MNC=HWV
SPECFILE=HWV.spec
PCMFILE=HWV.pcm
SRC=ptrhm.h dacsmread.txt /usr/local/share/huarp/freemem.tmc
SRC+=base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc
SRC+=T10K75KU.tmc ptrhm.cc vl_temp.tmc pwrmon.tmc
SRC+=/usr/local/share/huarp/cpu_usage.tmc
SRC+=/usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc
SRC+=SWData.tmc SWData.h ai_init.tmc ptrh_chk.tmc cnt_init.tmc
SRC+=idx64col.tmc sspcol.tmc vl_temp_col.tmc ptrhm_col.cc
SRC+=/usr/local/share/huarp/freemem_col.tmc
SRC+=/usr/local/share/huarp/DACS_ID.tmc
SRC+=/usr/local/share/huarp/cpu_usage_col.tmc
SRC+=/usr/local/share/huarp/tmdf_col.tmc dacsmread_col.tmc
SRC+=IWG1_col.tmc SWData_col.tmc -lsubbus
SRC+=/usr/local/share/huarp/root.cmd
SRC+=/usr/local/share/huarp/getcon.cmd
SRC+=/usr/local/share/huarp/idx64.cmd
SRC+=/usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd
SRC+=ssp.cmd ai.cmd ao.cmd soldrv.cmd waves.cmd fail.cmd SWData.cmd
SRC+=/usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc
SRC+=idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc HWVmr2.tmc
SRC+=LyAmr/LyAmrSample.cc LyAmr/Circular.cc LyAmr/LyAmrAvg.cc
SRC+=SSPrtg.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRC+=/usr/local/share/oui/cic.oui IWG1.tbl LyAmr/UDP.cc UDP.tmc
SRC+=-lsocket IRVf.tmc HWV.tma HWV.sws HWVcal.tma HWV.doit
SRC+=HWVcal.doit ly.doit A.sol B.sol C.sol hwveng.cdf hwvraw.cdf
SRC+=hwv.cdf hhh.cdf lyamr.cdf HWVmr2.oui HWV.pcm
TOOL=HWV.spec Makefile
SCRIPT=interact runfile.FF runfile_cal dccc.dccc idx64.idx64
SCRIPT+=hwv_analysis
OBJ=waves.cmd waves.out waves.tmc waves.m waves.log address.h
OBJ+=dacsmread.tmc dacsmread_col.tmc HWVcol.cc tm.dac HWVcoloui.c
OBJ+=HWVcoloui.o HWVcol.o ptrhm.o ptrhm_col.o HWVcmd.cc HWVcmd.dat
OBJ+=HWVsrvr.o HWVsrvroui.c HWVsrvroui.o HWVtbl.tmc lyalphatbl.tmc
OBJ+=hktbl.tmc labtbl.tmc IWG1tbl.tmc HWVdisp.cc HWVdispoui.c
OBJ+=HWVdispoui.o HWVdisp.o LyAmrSample.o Circular.o LyAmrAvg.o
OBJ+=HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
OBJ+=IWG1tblnc.tmc HWVdispnc.cc HWVdispncoui.c HWVdispncoui.o
OBJ+=HWVdispnc.o lydisp.cc lydispoui.c lydispoui.o lydisp.o
OBJ+=lydispnc.cc lydispncoui.c lydispncoui.o lydispnc.o
OBJ+=lyamrudpext.cc lyamrudpextoui.c lyamrudpextoui.o lyamrudpext.o
OBJ+=UDP.o HWVsws.tma HWValgoa.tmc HWValgo.cc HWValgooui.c
OBJ+=HWValgooui.o HWValgo.o HWVcalalgoa.tmc HWVcalalgo.cc
OBJ+=HWVcalalgooui.c HWVcalalgooui.o HWVcalalgo.o doit.dep
OBJ+=caldoit.dep lydoit.dep hwvengextcdf.oui hwvengextcdf.tmc
OBJ+=hwvengext.cc hwvengextoui.c hwvengextoui.o hwvengext.o
OBJ+=hwvrawextcdf.oui hwvrawextcdf.tmc hwvrawext.cc hwvrawextoui.c
OBJ+=hwvrawextoui.o hwvrawext.o hwvextcdf.oui hwvextcdf.tmc hwvext.cc
OBJ+=hwvextoui.c hwvextoui.o hwvext.o hhhextcdf.oui hhhextcdf.tmc
OBJ+=hhhext.cc hhhextoui.c hhhextoui.o hhhext.o lyamrextcdf.oui
OBJ+=lyamrextcdf.tmc lyamrext.cc lyamrextoui.c lyamrextoui.o
OBJ+=lyamrext.o HWVclt.o HWVcltoui.c HWVcltoui.o HWVcltnc.o
OBJ+=HWVcltncoui.c HWVcltncoui.o HWVtbl.tmc.dep lyalphatbl.tmc.dep
OBJ+=hktbl.tmc.dep labtbl.tmc.dep IWG1tbl.tmc.dep HWVtblnc.tmc.dep
OBJ+=lyalphatblnc.tmc.dep hktblnc.tmc.dep labtblnc.tmc.dep
OBJ+=IWG1tblnc.tmc.dep
TGT=HWVcol HWVsrvr HWVdisp HWVdispnc lydisp lydispnc lyamrudpext
TGT+=HWValgo HWVcalalgo doit caldoit lydoit A.sft B.sft C.sft
TGT+=hwvengext hwvrawext hwvext hhhext lyamrext HWVclt HWVcltnc
IGNORE=
DISTRIB=waves.out A.sft ../IWG1/IWG1 HWV.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit caldoit lydoit
SRCDIST=waves.qcli waves.m HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRCDIST+=IWG1.tbl HWV.tma HWVcal.tma A.sol B.sol C.sol
SRCDIST+=/usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc
SRCDIST+=ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc
SRCDIST+=ptrhm.cc vl_temp.tmc pwrmon.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc
SRCDIST+=SWData.tmc SWData.h
TMCBASE=/usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc
TMCBASE+=ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc
TMCBASE+=ptrhm.cc vl_temp.tmc pwrmon.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc
TMCBASE+=SWData.tmc SWData.h
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/idx64.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd
CMDBASE+=qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd waves.cmd fail.cmd
CMDBASE+=SWData.cmd SWData.h
COLBASE=ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc
COLBASE+=sspcol.tmc vl_temp_col.tmc ptrhm_col.cc
COLBASE+=/usr/local/share/huarp/freemem_col.tmc
COLBASE+=/usr/local/share/huarp/DACS_ID.tmc
COLBASE+=/usr/local/share/huarp/cpu_usage_col.tmc
COLBASE+=/usr/local/share/huarp/tmdf_col.tmc dacsmread_col.tmc
COLBASE+=IWG1_col.tmc SWData_col.tmc
SWSBASE=HWV.sws
QCLIBASE=
GENUIBASE=
EXTBASE=
SPECDEPBASE=
SPECTGTBASE=
SPECTGTMISS:=$(foreach file,$(SPECTGTBASE),$(if $(wildcard $(file)),,$(file)))
AG_CPPFLAGS=
PHTGT=HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc IWG1tbl.tmc
SOURCE=$(SRC) $(TOOL) $(SCRIPT)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/hwv
include /usr/local/share/huarp/appgen.mk

.PHONY : all all-dist extdistribution distribution clean clean-dist check_photon

IGNOREFILE=.gitignore
all : check_photon $(TGT) $(IGNOREFILE)
all-dist : all $(DSTRB) $(SRCDIST) VERSION
Makefile $(SPECTGTMISS) : HWV.spec $(SPECDEPBASE)
	appgen HWV.spec
VERSION=`cat VERSION`
extdistribution : all-dist
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@[ ! -f $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) ] || \
	  cmp -s $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) $(PCMFILE) || \
	  ( echo "$(PCMFILE) changed without VERSION update"; false )
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
check_photon :
ifeq ($(WPHOTON),YES)
	@for tgt in $(PHTGT); do \
	  cmp -s $$tgt /usr/local/share/huarp/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \
	done; true
endif
HWVcol : HWVcol.o ptrhm.o ptrhm_col.o HWVcoloui.o
	$(LINK.privCXX) HWVcol.o ptrhm.o ptrhm_col.o HWVcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVcoloui.c
	$(PROMOTE) HWVcol
HWVsrvr : HWVsrvr.o HWVsrvroui.o
	$(LINK.privCXX) HWVsrvr.o HWVsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVsrvroui.c
	$(PROMOTE) HWVsrvr
HWVdisp : HWVdisp.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o HWVdispoui.o
	$(LINK.normCXX) HWVdisp.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o HWVdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispoui.c
HWVdispnc : HWVdispnc.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o HWVdispncoui.o
	$(LINK.normCXX) HWVdispnc.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o HWVdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispncoui.c
lydisp : lydisp.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lydispoui.o
	$(LINK.normCXX) lydisp.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lydispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) lydispoui.c
lydispnc : lydispnc.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lydispncoui.o
	$(LINK.normCXX) lydispnc.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lydispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) lydispncoui.c
lyamrudpext : lyamrudpext.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o UDP.o lyamrudpextoui.o
	$(LINK.normCXX) lyamrudpext.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o UDP.o lyamrudpextoui.o -lsocket -ltmpp -ltm -lnort
	$(OUIUSE) lyamrudpextoui.c
HWValgo : HWValgo.o ptrhm.o HWValgooui.o
	$(LINK.normCXX) HWValgo.o ptrhm.o HWValgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) HWValgooui.c
HWVcalalgo : HWVcalalgo.o ptrhm.o HWVcalalgooui.o
	$(LINK.normCXX) HWVcalalgo.o ptrhm.o HWVcalalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) HWVcalalgooui.c
doit : HWV.doit
	mkdoit3 -o doit  HWV.doit
caldoit : HWVcal.doit
	mkdoit3 -o caldoit  HWVcal.doit
lydoit : ly.doit
	mkdoit3 -o lydoit  ly.doit
A.sft : A.sol
	solfmt -oA.sft  A.sol
B.sft : B.sol
	solfmt -oB.sft  B.sol
C.sft : C.sol
	solfmt -oC.sft  C.sol
hwvengext : hwvengext.o ptrhm.o hwvengextoui.o
	$(LINK.normCXX) hwvengext.o ptrhm.o hwvengextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) hwvengextoui.c
hwvrawext : hwvrawext.o ptrhm.o hwvrawextoui.o
	$(LINK.normCXX) hwvrawext.o ptrhm.o hwvrawextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) hwvrawextoui.c
hwvext : hwvext.o ptrhm.o hwvextoui.o
	$(LINK.normCXX) hwvext.o ptrhm.o hwvextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) hwvextoui.c
hhhext : hhhext.o ptrhm.o hhhextoui.o
	$(LINK.normCXX) hhhext.o ptrhm.o hhhextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) hhhextoui.c
lyamrext : lyamrext.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lyamrextoui.o
	$(LINK.normCXX) lyamrext.o ptrhm.o LyAmrSample.o Circular.o LyAmrAvg.o lyamrextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) lyamrextoui.c
HWVclt : HWVclt.o HWVcltoui.o
	$(LINK.normCXX) HWVclt.o HWVcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltoui.c
HWVcltnc : HWVcltnc.o HWVcltncoui.o
	$(LINK.normCXX) HWVcltnc.o HWVcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltncoui.c
HWVcol.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc vl_temp_col.tmc /usr/local/share/huarp/freemem_col.tmc /usr/local/share/huarp/DACS_ID.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc dacsmread_col.tmc IWG1_col.tmc SWData_col.tmc VERSION
	$(TMC.col) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc vl_temp_col.tmc /usr/local/share/huarp/freemem_col.tmc /usr/local/share/huarp/DACS_ID.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc dacsmread_col.tmc IWG1_col.tmc SWData_col.tmc
HWVcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVcoloui.o : HWVcoloui.c SWData.h
HWVcol.o : HWVcol.cc SWData.h
ptrhm.o : ptrhm.cc SWData.h
ptrhm_col.o : ptrhm_col.cc SWData.h
HWVcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd waves.cmd fail.cmd SWData.cmd
	$(CMDGEN) -d HWVcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd waves.cmd fail.cmd SWData.cmd
HWVsrvr.o : HWVcmd.cc SWData.h
	$(COMPILE.srvr) HWVcmd.cc
HWVsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVsrvroui.o : HWVsrvroui.c SWData.h
HWVtbl.tmc : HWV.tbl
-include HWVtbl.tmc.dep
lyalphatbl.tmc : lyalpha.tbl
-include lyalphatbl.tmc.dep
hktbl.tmc : hk.tbl
-include hktbl.tmc.dep
labtbl.tmc : lab.tbl
-include labtbl.tmc.dep
IWG1tbl.tmc : IWG1.tbl
-include IWG1tbl.tmc.dep
HWVdisp.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc HWVmr2.tmc SSPrtg.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc IWG1tbl.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc HWVmr2.tmc SSPrtg.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc IWG1tbl.tmc
HWVdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispoui.o : HWVdispoui.c SWData.h
HWVdisp.o : HWVdisp.cc SWData.h
LyAmrSample.o : LyAmr/LyAmrSample.cc SWData.h
	$(COMPILE.cc) LyAmr/LyAmrSample.cc
Circular.o : LyAmr/Circular.cc SWData.h
	$(COMPILE.cc) LyAmr/Circular.cc
LyAmrAvg.o : LyAmr/LyAmrAvg.cc SWData.h
	$(COMPILE.cc) LyAmr/LyAmrAvg.cc
HWVtblnc.tmc : HWV.tbl
-include HWVtblnc.tmc.dep
lyalphatblnc.tmc : lyalpha.tbl
-include lyalphatblnc.tmc.dep
hktblnc.tmc : hk.tbl
-include hktblnc.tmc.dep
labtblnc.tmc : lab.tbl
-include labtblnc.tmc.dep
IWG1tblnc.tmc : IWG1.tbl
-include IWG1tblnc.tmc.dep
HWVdispnc.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc HWVmr2.tmc SSPrtg.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc IWG1tblnc.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc pwrmon_conv.tmc HWVmr2.tmc SSPrtg.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc IWG1tblnc.tmc
HWVdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispncoui.o : HWVdispncoui.c SWData.h
HWVdispnc.o : HWVdispnc.cc SWData.h
lydisp.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc digio.tmc HWVmr2.tmc lyalphatbl.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc digio.tmc HWVmr2.tmc lyalphatbl.tmc
lydispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispoui.o : lydispoui.c SWData.h
lydisp.o : lydisp.cc SWData.h
lydispnc.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc digio.tmc HWVmr2.tmc lyalphatblnc.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc digio.tmc HWVmr2.tmc lyalphatblnc.tmc
lydispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispncoui.o : lydispncoui.c SWData.h
lydispnc.o : lydispnc.cc SWData.h
lyamrudpext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc HWVmr2.tmc UDP.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc /usr/local/share/huarp/flttime.tmc HWVmr2.tmc UDP.tmc
lyamrudpextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lyamrudpextoui.o : lyamrudpextoui.c SWData.h
lyamrudpext.o : lyamrudpext.cc SWData.h
UDP.o : LyAmr/UDP.cc SWData.h
	$(COMPILE.cc) LyAmr/UDP.cc
HWVsws.tma : HWV.sws
	$(COMPILE.sws) HWV.sws
HWValgoa.tmc : HWV.tma HWVsws.tma HWVsrvr
	$(SERVER) ./HWVsrvr
	$(TMCALGO) -V "`./HWVsrvr -R`" HWV.tma HWVsws.tma
HWValgo.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc HWValgoa.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc HWValgoa.tmc
HWValgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWValgooui.o : HWValgooui.c SWData.h
HWValgo.o : HWValgo.cc SWData.h
HWVcalalgoa.tmc : HWVcal.tma HWVsws.tma HWVsrvr
	$(SERVER) ./HWVsrvr
	$(TMCALGO) -V "`./HWVsrvr -R`" HWVcal.tma HWVsws.tma
HWVcalalgo.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc HWVcalalgoa.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc HWVcalalgoa.tmc
HWVcalalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVcalalgooui.o : HWVcalalgooui.c SWData.h
HWVcalalgo.o : HWVcalalgo.cc SWData.h
doit.dep : HWV.doit
	mkdoit3 -M -o doit  HWV.doit
-include doit.dep
caldoit.dep : HWVcal.doit
	mkdoit3 -M -o caldoit  HWVcal.doit
-include caldoit.dep
lydoit.dep : ly.doit
	mkdoit3 -M -o lydoit  ly.doit
-include lydoit.dep
hwvengextcdf.oui : hwveng.cdf
	$(EDF2OUI) hwveng.cdf
hwvengextcdf.tmc : hwveng.cdf
	$(EDF2EXT) hwveng.cdf
hwvengext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc hwvengextcdf.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc IRVf.tmc hwvengextcdf.tmc
hwvengextoui.c : hwvengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvengextoui.o : hwvengextoui.c SWData.h
hwvengext.o : hwvengext.cc SWData.h
hwvrawextcdf.oui : hwvraw.cdf
	$(EDF2OUI) hwvraw.cdf
hwvrawextcdf.tmc : hwvraw.cdf
	$(EDF2EXT) hwvraw.cdf
hwvrawext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc hwvrawextcdf.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc ptrh_conv.tmc hwvrawextcdf.tmc
hwvrawextoui.c : hwvrawextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvrawextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvrawextoui.o : hwvrawextoui.c SWData.h
hwvrawext.o : hwvrawext.cc SWData.h
hwvextcdf.oui : hwv.cdf
	$(EDF2OUI) hwv.cdf
hwvextcdf.tmc : hwv.cdf
	$(EDF2EXT) hwv.cdf
hwvext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc hwvextcdf.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc hwvextcdf.tmc
hwvextoui.c : hwvextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvextoui.o : hwvextoui.c SWData.h
hwvext.o : hwvext.cc SWData.h
hhhextcdf.oui : hhh.cdf
	$(EDF2OUI) hhh.cdf
hhhextcdf.tmc : hhh.cdf
	$(EDF2EXT) hhh.cdf
hhhext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc hhhextcdf.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc hhhextcdf.tmc
hhhextoui.c : hhhextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hhhextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hhhextoui.o : hhhextoui.c SWData.h
hhhext.o : hhhext.cc SWData.h
lyamrextcdf.oui : lyamr.cdf
	$(EDF2OUI) lyamr.cdf
lyamrextcdf.tmc : lyamr.cdf
	$(EDF2EXT) lyamr.cdf
lyamrext.cc : /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc HWVmr2.tmc lyamrextcdf.tmc VERSION
	$(TMC) /usr/local/share/huarp/freemem.tmc base.tmc idx64.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc pwrmon.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc dacsmread.tmc IWG1.tmc SWData.tmc HWVmr2.tmc lyamrextcdf.tmc
lyamrextoui.c : HWVmr2.oui lyamrextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) HWVmr2.oui lyamrextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lyamrextoui.o : lyamrextoui.c SWData.h
lyamrext.o : lyamrext.cc SWData.h
HWVclt.o : HWVcmd.cc SWData.h
	$(COMPILE.clt) HWVcmd.cc
HWVcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
HWVcltoui.o : HWVcltoui.c SWData.h
HWVcltnc.o : HWVcmd.cc SWData.h
	$(COMPILE.cltnc) HWVcmd.cc
HWVcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
HWVcltncoui.o : HWVcltncoui.c SWData.h
SWData.h SWData.tmc SWData_col.tmc SWData.cmd :  HWV.sws
	swscomp -o SWData  HWV.sws

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
clean-dist : clean
$(IGNOREFILE) : Makefile
	@for i in $(OBJECT) $(IGNORE) $(TARGET); do echo "$$i"; done >$(IGNOREFILE)
COLFLAGS=-Haddress.h
CXXFLAGS=-g
CPPFLAGS+=-I ../IWG1
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
../IWG1/IWG1 :
	cd ../IWG1 && make
