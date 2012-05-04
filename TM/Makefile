# Makefile Generated Fri May 04 15:14:14 EDT 2012
MNC=HWV
HOMEDIR=/home/hwv/src/TM
SPECFILE=HWV.spec
SRC=ptrhm.h base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
SRC+=T30K75KU.tmc T10K75KU.tmc ptrhm.cc vl_temp.tmc ai_init.tmc
SRC+=ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
SRC+=vl_temp_col.tmc ptrhm_col.cc idx64drv.cmd dccc.cmd qcli.cmd
SRC+=ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
SRC+=qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc
SRC+=ptrh_conv.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl HWV.tma
SRC+=HWV.doit ly.doit A.sol B.sol C.sol hwveng.cdf hwvraw.cdf hwv.cdf
SRC+=hhh.cdf PT.cdf
TOOL=HWV.spec Makefile
SCRIPT=interact runfile.FF dccc.dccc idx64.idx64
OBJ=waves.cmd waves.out waves.tmc waves.m waves.log address.h
OBJ+=HWVcol.cc HWV.pcm tm.dac HWVcoloui.c HWVcoloui.o HWVcol.o
OBJ+=ptrhm.o ptrhm_col.o HWVcmd.cc HWVcmd.dat HWVsrvr.o HWVsrvroui.c
OBJ+=HWVsrvroui.o HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
OBJ+=HWVdisp.cc HWVdispoui.c HWVdispoui.o HWVdisp.o HWVtblnc.tmc
OBJ+=lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc HWVdispnc.cc
OBJ+=HWVdispncoui.c HWVdispncoui.o HWVdispnc.o lydisp.cc lydispoui.c
OBJ+=lydispoui.o lydisp.o lydispnc.cc lydispncoui.c lydispncoui.o
OBJ+=lydispnc.o HWValgoa.tmc HWValgo.cc HWValgooui.c HWValgooui.o
OBJ+=HWValgo.o doit.dep lydoit.dep hwvengextcdf.oui hwvengext.tmc
OBJ+=hwvengext.cc hwvengextoui.c hwvengextoui.o hwvengext.o
OBJ+=hwvrawextcdf.oui hwvrawext.tmc hwvrawext.cc hwvrawextoui.c
OBJ+=hwvrawextoui.o hwvrawext.o hwvextcdf.oui hwvext.tmc hwvext.cc
OBJ+=hwvextoui.c hwvextoui.o hwvext.o hhhextcdf.oui hhhext.tmc
OBJ+=hhhext.cc hhhextoui.c hhhextoui.o hhhext.o PTextcdf.oui
OBJ+=PText.tmc PText.cc PTextoui.c PTextoui.o PText.o HWVclt.o
OBJ+=HWVcltoui.c HWVcltoui.o HWVcltnc.o HWVcltncoui.c HWVcltncoui.o
TGT=HWVcol HWVsrvr HWVdisp HWVdispnc lydisp lydispnc HWValgo doit
TGT+=lydoit A.sft B.sft C.sft hwvengext hwvrawext hwvext hhhext PText
TGT+=HWVclt HWVcltnc
DISTRIB=waves.out A.sft HWV.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit lydoit
SRCDIST=waves.qcli waves.m HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRCDIST+=HWV.tma A.sol B.sol C.sol base.tmc idx64.tmc swstat.tmc
SRCDIST+=ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc
SRCDIST+=ptrhm.cc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
NONRCS=
TMCBASE=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
TMCBASE+=T30K75KU.tmc T10K75KU.tmc ptrhm.cc vl_temp.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/idx64.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd
CMDBASE+=qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd
CMDBASE+=waves.cmd
COLBASE=
SWSBASE=
QCLIBASE=
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/hwv
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT) .cvsignore
Makefile : HWV.spec
	appgen HWV.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST) VERSION
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
HWVcol : HWVcol.o ptrhm.o ptrhm_col.o HWVcoloui.o
	$(LINK.privCXX) HWVcol.o ptrhm.o ptrhm_col.o HWVcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVcoloui.c
	$(PROMOTE) HWVcol
HWVsrvr : HWVsrvr.o HWVsrvroui.o
	$(LINK.privCXX) HWVsrvr.o HWVsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVsrvroui.c
	$(PROMOTE) HWVsrvr
HWVdisp : HWVdisp.o ptrhm.o HWVdispoui.o
	$(LINK.normCXX) HWVdisp.o ptrhm.o HWVdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispoui.c
HWVdispnc : HWVdispnc.o ptrhm.o HWVdispncoui.o
	$(LINK.normCXX) HWVdispnc.o ptrhm.o HWVdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispncoui.c
lydisp : lydisp.o ptrhm.o lydispoui.o
	$(LINK.normCXX) lydisp.o ptrhm.o lydispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) lydispoui.c
lydispnc : lydispnc.o ptrhm.o lydispncoui.o
	$(LINK.normCXX) lydispnc.o ptrhm.o lydispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) lydispncoui.c
HWValgo : HWValgo.o ptrhm.o HWValgooui.o
	$(LINK.normCXX) HWValgo.o ptrhm.o HWValgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) HWValgooui.c
doit : HWV.doit
	mkdoit3 -o doit  HWV.doit
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
PText : PText.o ptrhm.o PTextoui.o
	$(LINK.normCXX) PText.o ptrhm.o PTextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) PTextoui.c
HWVclt : HWVclt.o HWVcltoui.o
	$(LINK.normCXX) HWVclt.o HWVcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltoui.c
HWVcltnc : HWVcltnc.o HWVcltncoui.o
	$(LINK.normCXX) HWVcltnc.o HWVcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltncoui.c
HWVcol.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ai_init.tmc /usr/local/share/huarp/DACS_ID.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc vl_temp_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
	$(TMC.col) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ai_init.tmc /usr/local/share/huarp/DACS_ID.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc vl_temp_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
HWVcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVcoloui.o : HWVcoloui.c
HWVcol.o : HWVcol.cc
ptrhm.o : ptrhm.cc
ptrhm_col.o : ptrhm_col.cc
HWVcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
	$(CMDGEN) -d HWVcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
HWVsrvr.o : HWVcmd.cc
	$(COMPILE.srvr) HWVcmd.cc
HWVsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVsrvroui.o : HWVsrvroui.c
HWVtbl.tmc : HWV.tbl
lyalphatbl.tmc : lyalpha.tbl
hktbl.tmc : hk.tbl
labtbl.tmc : lab.tbl
HWVdisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
HWVdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispoui.o : HWVdispoui.c
HWVdisp.o : HWVdisp.cc
HWVtblnc.tmc : HWV.tbl
lyalphatblnc.tmc : lyalpha.tbl
hktblnc.tmc : hk.tbl
labtblnc.tmc : lab.tbl
HWVdispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
HWVdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispncoui.o : HWVdispncoui.c
HWVdispnc.o : HWVdispnc.cc
lydisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatbl.tmc
lydispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispoui.o : lydispoui.c
lydisp.o : lydisp.cc
lydispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatblnc.tmc
lydispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispncoui.o : lydispncoui.c
lydispnc.o : lydispnc.cc
HWValgoa.tmc : HWV.tma HWVsrvr
	$(SERVER) ./HWVsrvr
	$(TMCALGO) -V "`./HWVsrvr -R`" HWV.tma
HWValgo.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc HWValgoa.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc HWValgoa.tmc
HWValgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWValgooui.o : HWValgooui.c
HWValgo.o : HWValgo.cc
doit.dep : HWV.doit
	mkdoit3 -M -o doit  HWV.doit
-include doit.dep
lydoit.dep : ly.doit
	mkdoit3 -M -o lydoit  ly.doit
-include lydoit.dep
hwvengextcdf.oui : hwveng.cdf
	$(EDF2OUI) hwveng.cdf
hwvengext.tmc : hwveng.cdf
	$(EDF2EXT) hwveng.cdf
hwvengext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc hwvengext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc hwvengext.tmc
hwvengextoui.c : hwvengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvengextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvengextoui.o : hwvengextoui.c
hwvengext.o : hwvengext.cc
hwvrawextcdf.oui : hwvraw.cdf
	$(EDF2OUI) hwvraw.cdf
hwvrawext.tmc : hwvraw.cdf
	$(EDF2EXT) hwvraw.cdf
hwvrawext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc hwvrawext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc ptrh_conv.tmc hwvrawext.tmc
hwvrawextoui.c : hwvrawextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvrawextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvrawextoui.o : hwvrawextoui.c
hwvrawext.o : hwvrawext.cc
hwvextcdf.oui : hwv.cdf
	$(EDF2OUI) hwv.cdf
hwvext.tmc : hwv.cdf
	$(EDF2EXT) hwv.cdf
hwvext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc hwvext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc hwvext.tmc
hwvextoui.c : hwvextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvextoui.o : hwvextoui.c
hwvext.o : hwvext.cc
hhhextcdf.oui : hhh.cdf
	$(EDF2OUI) hhh.cdf
hhhext.tmc : hhh.cdf
	$(EDF2EXT) hhh.cdf
hhhext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc hhhext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc hhhext.tmc
hhhextoui.c : hhhextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hhhextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hhhextoui.o : hhhextoui.c
hhhext.o : hhhext.cc
PTextcdf.oui : PT.cdf
	$(EDF2OUI) PT.cdf
PText.tmc : PT.cdf
	$(EDF2EXT) PT.cdf
PText.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc PText.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc vl_temp.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc PText.tmc
PTextoui.c : PTextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) PTextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
PTextoui.o : PTextoui.c
PText.o : PText.cc
HWVclt.o : HWVcmd.cc
	$(COMPILE.clt) HWVcmd.cc
HWVcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
HWVcltoui.o : HWVcltoui.c
HWVcltnc.o : HWVcmd.cc
	$(COMPILE.cltnc) HWVcmd.cc
HWVcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
HWVcltncoui.o : HWVcltncoui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
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
