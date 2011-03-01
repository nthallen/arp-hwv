&command
  : Set &ao_chan %lf (Volts) * {
      double N = $3 * 6553.6;
      unsigned short bits;
      if (N > 65535) N = 65535;
      if (N < 0) N = 0.;
      bits = (unsigned short) N;
      sbwr( $2, bits );
    }
  ;
&ao_chan <unsigned short>
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
  ;
