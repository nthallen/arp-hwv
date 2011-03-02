# Makefile Generated Wed Mar 02 09:30:38 EST 2011
MNC=HWV
HOMEDIR=/home/HWV/src/TM
SPECFILE=HWV.spec
SRC=base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc
SRC+=T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc
SRC+=sspcol.tmc idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd
SRC+=soldrv.cmd swstat.cmd waves.cmd qclibits.tmc sspflags.tmc
SRC+=idx64flag.tmc digio.tmc HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRC+=HWV.tma HWV.doit ly.doit A.sol
TOOL=HWV.spec Makefile
SCRIPT=interact dccc.dccc idx64.idx64
OBJ=waves.cmd waves.out waves.tmc waves.m waves.log address.h
OBJ+=HWVcol.cc HWV.pcm tm.dac HWVcoloui.c HWVcoloui.o HWVcol.o
OBJ+=HWVcmd.cc HWVcmd.dat HWVsrvr.o HWVsrvroui.c HWVsrvroui.o
OBJ+=HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc HWVdisp.cc
OBJ+=HWVdispoui.c HWVdispoui.o HWVdisp.o HWVtblnc.tmc
OBJ+=lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc HWVdispnc.cc
OBJ+=HWVdispncoui.c HWVdispncoui.o HWVdispnc.o HWValgoa.tmc
OBJ+=HWValgo.cc HWValgooui.c HWValgooui.o HWValgo.o lydisp.cc
OBJ+=lydispoui.c lydispoui.o lydisp.o lydispnc.cc lydispncoui.c
OBJ+=lydispncoui.o lydispnc.o doit.dep lydoit.dep HWVclt.o
OBJ+=HWVcltoui.c HWVcltoui.o HWVcltnc.o HWVcltncoui.c HWVcltncoui.o
TGT=HWVcol HWVsrvr HWVdisp HWVdispnc HWValgo lydisp lydispnc doit
TGT+=lydoit A.sft HWVclt HWVcltnc
DISTRIB=waves.out A.sft HWV.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit lydoit
SRCDIST=waves.qcli waves.m HWV.tbl lyalpha.tbl hk.tbl lab.tbl
SRCDIST+=HWV.tma A.sol base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc
SRCDIST+=waves.tmc T30K75KU.tmc T10K75KU.tmc
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
TGTDIR= $(TGTNODE)/home/HWV
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
HWVcol : HWVcol.o HWVcoloui.o
	$(LINK.privCXX) HWVcol.o HWVcoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVcoloui.c
	$(PROMOTE) HWVcol
HWVsrvr : HWVsrvr.o HWVsrvroui.o
	$(LINK.privCXX) HWVsrvr.o HWVsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HWVsrvroui.c
	$(PROMOTE) HWVsrvr
HWVdisp : HWVdisp.o HWVdispoui.o
	$(LINK.normCXX) HWVdisp.o HWVdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispoui.c
HWVdispnc : HWVdispnc.o HWVdispncoui.o
	$(LINK.normCXX) HWVdispnc.o HWVdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVdispncoui.c
HWValgo : HWValgo.o HWValgooui.o
	$(LINK.normCXX) HWValgo.o HWValgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) HWValgooui.c
lydisp : lydisp.o lydispoui.o
	$(LINK.normCXX) lydisp.o lydispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) lydispoui.c
lydispnc : lydispnc.o lydispncoui.o
	$(LINK.normCXX) lydispnc.o lydispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) lydispncoui.c
doit : HWV.doit
	mkdoit3 -o doit  HWV.doit
lydoit : ly.doit
	mkdoit3 -o lydoit  ly.doit
A.sft : A.sol
	solfmt -oA.sft  A.sol
HWVclt : HWVclt.o HWVcltoui.o
	$(LINK.normCXX) HWVclt.o HWVcltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltoui.c
HWVcltnc : HWVcltnc.o HWVcltncoui.o
	$(LINK.normCXX) HWVcltnc.o HWVcltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HWVcltncoui.c
HWVcol.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
	$(TMC.col) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc ai_init.tmc cnt_init.tmc idx64col.tmc sspcol.tmc
HWVcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HWVcoloui.o : HWVcoloui.c
HWVcol.o : HWVcol.cc
HWVcmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
	$(CMDGEN) -d HWVcmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd /usr/local/share/huarp/idx64.cmd idx64drv.cmd dccc.cmd qcli.cmd ssp.cmd ao.cmd soldrv.cmd swstat.cmd waves.cmd
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
HWVdisp.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HWVtbl.tmc lyalphatbl.tmc hktbl.tmc labtbl.tmc
HWVdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
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
HWVdispnc.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc /usr/local/share/huarp/flttime.tmc qclibits.tmc sspflags.tmc idx64flag.tmc digio.tmc HWVtblnc.tmc lyalphatblnc.tmc hktblnc.tmc labtblnc.tmc
HWVdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWVdispncoui.o : HWVdispncoui.c
HWVdispnc.o : HWVdispnc.cc
HWValgoa.tmc : HWV.tma HWVsrvr
	$(SERVER) ./HWVsrvr
	$(TMCALGO) -V "`./HWVsrvr -R`" HWV.tma
HWValgo.cc : base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc HWValgoa.tmc
	$(TMC) base.tmc idx64.tmc swstat.tmc ssp.tmc qcli.tmc waves.tmc T30K75KU.tmc T10K75KU.tmc HWValgoa.tmc
HWValgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HWValgooui.o : HWValgooui.c
HWValgo.o : HWValgo.cc
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
doit.dep : HWV.doit
	mkdoit3 -M -o doit  HWV.doit
-include doit.dep
lydoit.dep : ly.doit
	mkdoit3 -M -o lydoit  ly.doit
-include lydoit.dep
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
