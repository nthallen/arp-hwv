%{
  #include "hsatod.h"
%}
%INTERFACE <QCLI>

&command
  : &QCLI &qclicommand0 * { $1->Turf( $2 ); }
  : &QCLI Write &DAC_Val to &DAC_Num * {
        $1->Turf( "D%d:%d\n", $5, $3 );
      }
  : &QCLI Set &QCLI_T_Param to &QCLI_T_val * {
        $1->Turf( "%s:%d\n", $3, $5 );
      }
# : &QCLI Set Heater to %lf (Enter Voltage) Volts * {
#     double dbits = $5 * 3252.5 - 749.8;
#     if ( dbits < 0 ) dbits = 0;
#     if ( dbits > 65535 ) {
#       nl_error( 2,
#         "DAC3 requested value out of range: %lf V = %lf bits",
#         $5, dbits );
#     } else {
#       unsigned short ibits = (unsigned short)dbits;
#       $1->Turf( "D3:%u\n", ibits );
#     }
#   }
  ;

&QCLI <cmdif_rd *>
  : QCLI { $0 = &if_QCLI; }
  ;

&qclicommand0 <const char *>
  : Run { $0 = "RW\n"; }
  : Stop { $0 = "ST\n"; }
  : Clear Errors { $0 = "CE\n"; }
  : Exit { $0 = "QU\n"; }
  ;
&QCLI_T_Param <const char *>
  : Ton { $0 = "TN"; }
  : Toff { $0 = "TF"; }
  : Tpre { $0 = "TP"; }
  ;
&DAC_Val <short>
  : %d (Enter digital value) { $0 = $1; }
  ;
&DAC_Num <short>
  : DAC0 { $0 = 0; }
  : Ramp DAC { $0 = 1; }
  : DAC2 { $0 = 2; }
  : DAC3 { $0 = 3; }
  ;
&QCLI_T_val <unsigned short>
  : %d (Enter time in usecs) { $0 = $1; }
  ;
