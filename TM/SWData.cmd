%{
  #include "SWData.h"
  #ifdef SERVER
    SWData_t SWData;
  #endif
%}

%INTERFACE <SWData:DG/data>

&command
  : &SWTM * { if_SWData.Turf(); }
  ;
&SWTM
  : SW Status &SWStat { SWData.SWStat = $3; }
  ;
&SWStat <unsigned short>
  : Altitude Takeoff { $0 = SWS_TAKEOFF; }
  : Set %d { $0 = $2; }
  : Altitude Land { $0 = SWS_LAND; }
  : Laser Start { $0 = SWS_DFB_START; }
  : Laser Stop { $0 = SWS_DFB_STOP; }
  : Laser Select HHH and Start { $0 = SWS_DFB_HHH; }
  : Lamp Enable { $0 = SWS_H2O_ENABLE; }
  : Lamp Disable { $0 = SWS_H2O_DISABLE; }
  : LyA Use T_SFB1T { $0 = SWS_T_SFB1T; }
  : LyA Use T_HHH1T { $0 = SWS_T_HHH1T; }
  : LyA Use T_LFB_T { $0 = SWS_T_LFB_T; }
  : LyA Use P_UVB1 { $0 = SWS_P_UVB1; }
  : LyA Use P_SD_HP { $0 = SWS_P_SD_HP; }
  : LyA Use P_HHH1P { $0 = SWS_P_HHH1P; }
  : LyA Use P_LFT_P { $0 = SWS_P_LFT_P; }
  : Time Warp { $0 = SWS_TIME_WARP; }
  : ReadFile { $0 = SWS_READFILE; }
  : Shutdown { $0 = SWS_SHUTDOWN; }
  ;
