# Makefile Generated Tue Mar 29 13:39:05 CDT 2011
MNC=HWV
HOMEDIR=/home/hwv/src/TM
SPECFILE=HWV.spec
SRC=ptrh.h base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
SRC+=T30K75KU.tmc T10K75KU.tmc ptrh.cc ai_init.tmc ptrh_chk.tmc
SRC+=cnt_init.tmc idx64col.tmc sspcol.tmc ptrh_col.cc idx64drv.cmd
SRC+=dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd
SRC+=waves.cmd qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc
SRC+=digio.tmc ptrh_conv.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRC+=HWV.tma HWV.doit ly.doit A.sol B.sol C.sol hwveng.edf hwv.edf
SRC+=hhh.edf
TOOL=HWV.spec Makefile
SCRIPT=interact runfile.FF dccc.dccc idx64.idx64
OBJ=waves.cmd waves.out waves.tmc waves.m waves.log address.h
OBJ+=HWVcol.cc HWV.pcm tm.dac HWVcoloui.c HWVcoloui.o HWVcol.o ptrh.o
OBJ+=ptrh_col.o HWVcmd.cc HWVcmd.dat HWVsrvr.o HWVsrvroui.c
OBJ+=HWVsrvroui.o HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
OBJ+=HWVdisp.cc HWVdispoui.c HWVdispoui.o HWVdisp.o HWVtblnc.tmc
OBJ+=lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc HWVdispnc.cc
OBJ+=HWVdispncoui.c HWVdispncoui.o HWVdispnc.o lydisp.cc lydispoui.c
OBJ+=lydispoui.o lydisp.o lydispnc.cc lydispncoui.c lydispncoui.o
OBJ+=lydispnc.o HWValgoa.tmc HWValgo.cc HWValgooui.c HWValgooui.o
OBJ+=HWValgo.o doit.dep lydoit.dep hwvengextedf.oui hwvengext.tmc
OBJ+=hwvengext.cc hwvengextoui.c hwvengextoui.o hwvengext.o
OBJ+=hwvextedf.oui hwvext.tmc hwvext.cc hwvextoui.c hwvextoui.o
OBJ+=hwvext.o hhhextedf.oui hhhext.tmc hhhext.cc hhhextoui.c
OBJ+=hhhextoui.o hhhext.o HWVclt.o HWVcltoui.c HWVcltoui.o HWVcltnc.o
OBJ+=HWVcltncoui.c HWVcltncoui.o
TGT=HWVcol HWVsrvr HWVdisp HWVdispnc lydisp lydispnc HWValgo doit
TGT+=lydoit A.sft B.sft C.sft hwvengext hwvext hhhext HWVclt HWVcltnc
DISTRIB=waves.out A.sft HWV.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit lydoit
SRCDIST=waves.qcli waves.m HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRCDIST+=HWV.tma A.sol B.sol C.sol base.tmc idx64.tmc swstat.tmc
SRCDIST+=ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ptrh.cc
NONRCS=
TMCBASE=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
TMCBASE+=T30K75KU.tmc T10K75KU.tmc ptrh.cc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/idx64.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd
CMDBASE+=qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd
CMDBASE+=waves.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/hwv
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : HWV.spec
	appgen HWV.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
HWVcol : HWVcol.o ptrh.o ptrh_col.o HWVcoloui.o
	$(LINK.privCXX) HWVcol.o ptrh.o ptrh_col.o HWVcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVcoloui.c
	$(PROMOTE) HWVcol
HWVsrvr : HWVsrvr.o HWVsrvroui.o
	$(LINK.privCXX) HWVsrvr.o HWVsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVsrvroui.c
	$(PROMOTE) HWVsrvr
HWVdisp : HWVdisp.o ptrh.o HWVdispoui.o
	$(LINK.normCXX) HWVdisp.o ptrh.o HWVdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispoui.c
HWVdispnc : HWVdispnc.o ptrh.o HWVdispncoui.o
	$(LINK.normCXX) HWVdispnc.o ptrh.o HWVdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispncoui.c
lydisp : lydisp.o ptrh.o lydispoui.o
	$(LINK.normCXX) lydisp.o ptrh.o lydispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) lydispoui.c
lydispnc : lydispnc.o ptrh.o lydispncoui.o
	$(LINK.normCXX) lydispnc.o ptrh.o lydispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) lydispncoui.c
HWValgo : HWValgo.o ptrh.o HWValgooui.o
	$(LINK.normCXX) HWValgo.o ptrh.o HWValgooui.o -ltmpp -ltm -lnort
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
hwvengext : hwvengext.o ptrh.o hwvengextoui.o
	$(LINK.normCXX) hwvengext.o ptrh.o hwvengextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) hwvengextoui.c
hwvext : hwvext.o ptrh.o hwvextoui.o
	$(LINK.normCXX) hwvext.o ptrh.o hwvextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) hwvextoui.c
hhhext : hhhext.o ptrh.o hhhextoui.o
	$(LINK.normCXX) hhhext.o ptrh.o hhhextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) hhhextoui.c
HWVclt : HWVclt.o HWVcltoui.o
	$(LINK.normCXX) HWVclt.o HWVcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltoui.c
HWVcltnc : HWVcltnc.o HWVcltncoui.o
	$(LINK.normCXX) HWVcltnc.o HWVcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltncoui.c
HWVcol.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
	$(TMC.col) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc ptrh_chk.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
HWVcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVcoloui.o : HWVcoloui.c
HWVcol.o : HWVcol.cc
ptrh.o : ptrh.cc
ptrh_col.o : ptrh_col.cc
HWVcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
	$(CMDGEN) -d HWVcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd /usr/local/share/huarp/phrtg.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ai.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
HWVsrvr.o : HWVcmd.cc
	$(COMPILE.srvr) HWVcmd.cc
HWVsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVsrvroui.o : HWVsrvroui.c
HWVtbl.tmc : HWV.tbl
	$(TABLE) HWV.tbl
lyalphatbl.tmc : lyalpha.tbl
	$(TABLE) lyalpha.tbl
hktbl.tmc : hk.tbl
	$(TABLE) hk.tbl
labtbl.tmc : lab.tbl
	$(TABLE) lab.tbl
HWVdisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
HWVdispoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispoui.o : HWVdispoui.c
HWVdisp.o : HWVdisp.cc
HWVtblnc.tmc : HWV.tbl
	$(NCTABLE) HWV.tbl
lyalphatblnc.tmc : lyalpha.tbl
	$(NCTABLE) lyalpha.tbl
hktblnc.tmc : hk.tbl
	$(NCTABLE) hk.tbl
labtblnc.tmc : lab.tbl
	$(NCTABLE) lab.tbl
HWVdispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc SSPrtg.tmc idx64flag.tmc digio.tmc ptrh_conv.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
HWVdispncoui.c : /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) /usr/local/share/oui/cic.oui $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispncoui.o : HWVdispncoui.c
HWVdispnc.o : HWVdispnc.cc
lydisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatbl.tmc
lydispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispoui.o : lydispoui.c
lydisp.o : lydisp.cc
lydispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc digio.tmc lyalphatblnc.tmc
lydispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
lydispncoui.o : lydispncoui.c
lydispnc.o : lydispnc.cc
HWValgoa.tmc : HWV.tma HWVsrvr
	$(SERVER) ./HWVsrvr
	$(TMCALGO) -V "`./HWVsrvr -R`" HWV.tma
HWValgo.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ptrh_conv.tmc HWValgoa.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ptrh_conv.tmc HWValgoa.tmc
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
hwvengextedf.oui : hwveng.edf
	$(EDF2OUI) hwveng.edf
hwvengext.tmc : hwveng.edf
	$(EDF2EXT) hwveng.edf
hwvengext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ptrh_conv.tmc hwvengext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ptrh_conv.tmc hwvengext.tmc
hwvengextoui.c : hwvengextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvengextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvengextoui.o : hwvengextoui.c
hwvengext.o : hwvengext.cc
hwvextedf.oui : hwv.edf
	$(EDF2OUI) hwv.edf
hwvext.tmc : hwv.edf
	$(EDF2EXT) hwv.edf
hwvext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc hwvext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc hwvext.tmc
hwvextoui.c : hwvextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hwvextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hwvextoui.o : hwvextoui.c
hwvext.o : hwvext.cc
hhhextedf.oui : hhh.edf
	$(EDF2OUI) hhh.edf
hhhext.tmc : hhh.edf
	$(EDF2EXT) hhh.edf
hhhext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc hhhext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc hhhext.tmc
hhhextoui.c : hhhextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) hhhextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
hhhextoui.o : hhhextoui.c
hhhext.o : hhhext.cc
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
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
COLFLAGS=-Haddress.h
CXXFLAGS=-g
address.h : HWVcol.cc
HWVsrvr.o : address.h
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
