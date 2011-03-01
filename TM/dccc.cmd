%{
  #include "address.h"
%}

%INTERFACE <dccc:dccc>

&command
  : Command &on_off_cmd &cmd_on_off *
      { if_dccc.Turf("D%d\n", 2*$2+$3); }
# : &dccc_cmd * { if_dccc.Turf("D%d\n", $1); }
# : Preamp SetGain &preampgain * { if_dccc.Turf( "M%s\n", $3 ); }
  ;
&on_off_cmd <int>
  : Lamp Module A { $0 = 0; }
  : Lamp Module B { $0 = 1; }
  : Lamp Module C { $0 = 2; }
  : Lab Command 1 { $0 = 3; }
  : Lab Command 2 { $0 = 4; }
  : Mirror Heat Zone 1 { $0 = 5; }
  : Mirror Heat Zone 2 { $0 = 6; }
  : Mirror Heat Zone 3 { $0 = 7; }
  : Mirror Heat Zone 4 { $0 = 8; }
  : Air A { $0 = 9; }
  : Air B { $0 = 10; }
  : Cmd_11 { $0 = 11; }
  : QCLI Reset { $0 = 24; }
  : Chopper A { $0 = 25; }
  : Chopper B { $0 = 26; }
  : Chopper C { $0 = 27; }
  ;

&cmd_on_off <int>
  : On { $0 = 0; }
  : Off { $0 = 1; }
  ;
