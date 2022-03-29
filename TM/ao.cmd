%{
  #include <stdint.h>
%}
&command
  : Set &ao_chan %lf (Volts) * {
      double N = $3 * 6553.6;
      uint16_t bits;
      if (N > 65535) N = 65535;
      if (N < 0) N = 0.;
      bits = (uint16_t) N;
      sbwr( $2, bits );
    }
  ;
&ao_chan <uint16_t>
  : Axis A Heat Set Pt { $0 = HtASt_Address; }
  : Axis A RF Set Pt { $0 = RFASt_Address; }
  : Axis B Heat Set Pt { $0 = HtBSt_Address; }
  : Axis B RF Set Pt { $0 = RFBSt_Address; }
  : Axis C Heat Set Pt { $0 = HtCSt_Address; }
  : Axis C RF Set Pt { $0 = RFCSt_Address; }
  : Mirror Temp 1 Set Pt { $0 = MZ1St_Address; }
  : Mirror Temp 2 Set Pt { $0 = MZ2St_Address; }
  : Mirror Temp 3 Set Pt { $0 = MZ3St_Address; }
  : Mirror Temp 4 Set Pt { $0 = MZ4St_Address; }
  : Lab Flow Bubbler Set Pt { $0 = LFBSt_Address; }
  : Lab Flow Air Set Pt { $0 = LFAirSt_Address; }
  ;
