# Makefile Generated Tue Mar 01 10:15:38 EST 2011
MNC=HHH
HOMEDIR=/home/HHH/src/TM
SPECFILE=HHH.spec
SRC=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
SRC+=T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc
SRC+=sspcol.tmc idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd
SRC+=soldrv.cmd swstat.cmd waves.cmd qclibits.tmc sspflags.tmc
SRC+=idx64flag.tmc digio.tmc HHH.tbl lyalpha.tbl hk.tbl lab.tbl
SRC+=HHH.doit ly.doit A.sol testext.tmc
TOOL=HHH.spec Makefile
SCRIPT=interact dccc.dccc idx64.idx64
OBJ=waves.cmd waves.out waves.tmc waves.m waves.log address.h
OBJ+=HHHcol.cc HHH.pcm tm.dac HHHcoloui.c HHHcoloui.o HHHcol.o
OBJ+=HHHcmd.cc HHHcmd.dat HHHsrvr.o HHHsrvroui.c HHHsrvroui.o
OBJ+=HHHtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc HHHdisp.cc
OBJ+=HHHdispoui.c HHHdispoui.o HHHdisp.o HHHtblnc.tmc
OBJ+=lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc HHHdispnc.cc
OBJ+=HHHdispncoui.c HHHdispncoui.o HHHdispnc.o lydisp.cc lydispoui.c
OBJ+=lydispoui.o lydisp.o lydispnc.cc lydispncoui.c lydispncoui.o
OBJ+=lydispnc.o doit.dep lydoit.dep testext.cc testextoui.c
OBJ+=testextoui.o testext.o HHHclt.o HHHcltoui.c HHHcltoui.o
OBJ+=HHHcltnc.o HHHcltncoui.c HHHcltncoui.o
TGT=HHHcol HHHsrvr HHHdisp HHHdispnc lydisp lydispnc doit lydoit
TGT+=A.sft testext HHHclt HHHcltnc
DISTRIB=waves.out A.sft HHH.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit lydoit
SRCDIST=waves.qcli waves.m HHH.tbl lyalpha.tbl hk.tbl lab.tbl A.sol
SRCDIST+=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
SRCDIST+=T30K75KU.tmc T10K75KU.tmc
NONRCS=
TMCBASE=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
TMCBASE+=T30K75KU.tmc T10K75KU.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
CMDBASE+=/usr/local/share/huarp/idx64.cmd idx64drv.cmd dccc.cmd
CMDBASE+=qcli.cmd ssp.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/HHH
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : HHH.spec
	appgen HHH.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
HHHcol : HHHcol.o HHHcoloui.o
	$(LINK.privCXX) HHHcol.o HHHcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HHHcoloui.c
	$(PROMOTE) HHHcol
HHHsrvr : HHHsrvr.o HHHsrvroui.o
	$(LINK.privCXX) HHHsrvr.o HHHsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HHHsrvroui.c
	$(PROMOTE) HHHsrvr
HHHdisp : HHHdisp.o HHHdispoui.o
	$(LINK.normCXX) HHHdisp.o HHHdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HHHdispoui.c
HHHdispnc : HHHdispnc.o HHHdispncoui.o
	$(LINK.normCXX) HHHdispnc.o HHHdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HHHdispncoui.c
lydisp : lydisp.o lydispoui.o
	$(LINK.normCXX) lydisp.o lydispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) lydispoui.c
lydispnc : lydispnc.o lydispncoui.o
	$(LINK.normCXX) lydispnc.o lydispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) lydispncoui.c
doit : HHH.doit
	mkdoit3 -o doit  HHH.doit
lydoit : ly.doit
	mkdoit3 -o lydoit  ly.doit
A.sft : A.sol
	solfmt -oA.sft  A.sol
testext : testext.o testextoui.o
	$(LINK.normCXX) testext.o testextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) testextoui.c
HHHclt : HHHclt.o HHHcltoui.o
	$(LINK.normCXX) HHHclt.o HHHcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HHHcltoui.c
HHHcltnc : HHHcltnc.o HHHcltncoui.o
	$(LINK.normCXX) HHHcltnc.o HHHcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HHHcltncoui.c
HHHcol.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
	$(TMC.col) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
HHHcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HHHcoloui.o : HHHcoloui.c
HHHcol.o : HHHcol.cc
HHHcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
	$(CMDGEN) -d HHHcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
HHHsrvr.o : HHHcmd.cc
	$(COMPILE.srvr) HHHcmd.cc
HHHsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HHHsrvroui.o : HHHsrvroui.c
HHHtbl.tmc : HHH.tbl
	$(TABLE) HHH.tbl
lyalphatbl.tmc : lyalpha.tbl
	$(TABLE) lyalpha.tbl
hktbl.tmc : hk.tbl
	$(TABLE) hk.tbl
labtbl.tmc : lab.tbl
	$(TABLE) lab.tbl
HHHdisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HHHtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HHHtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
HHHdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HHHdispoui.o : HHHdispoui.c
HHHdisp.o : HHHdisp.cc
HHHtblnc.tmc : HHH.tbl
	$(NCTABLE) HHH.tbl
lyalphatblnc.tmc : lyalpha.tbl
	$(NCTABLE) lyalpha.tbl
hktblnc.tmc : hk.tbl
	$(NCTABLE) hk.tbl
labtblnc.tmc : lab.tbl
	$(NCTABLE) lab.tbl
HHHdispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HHHtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HHHtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
HHHdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HHHdispncoui.o : HHHdispncoui.c
HHHdispnc.o : HHHdispnc.cc
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
doit.dep : HHH.doit
	mkdoit3 -M -o doit  HHH.doit
-include doit.dep
lydoit.dep : ly.doit
	mkdoit3 -M -o lydoit  ly.doit
-include lydoit.dep
testext.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc testext.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc testext.tmc
testextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
testextoui.o : testextoui.c
testext.o : testext.cc
HHHclt.o : HHHcmd.cc
	$(COMPILE.clt) HHHcmd.cc
HHHcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
HHHcltoui.o : HHHcltoui.c
HHHcltnc.o : HHHcmd.cc
	$(COMPILE.cltnc) HHHcmd.cc
HHHcltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
HHHcltncoui.o : HHHcltncoui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
COLFLAGS=-Haddress.h
CXXFLAGS=-g
address.h : HHHcol.cc
HHHsrvr.o : address.h
waves.cmd waves.out waves.tmc waves.m : waves.qcli
	qclicomp -o waves.out -c waves.cmd -d waves.tmc \
	  -v waves.log -m waves.m waves.qcli || \
	  ( rm -f waves.out waves.cmd waves.tmc waves.log waves.m; false )
