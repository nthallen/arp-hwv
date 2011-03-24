%{
  #include "swstat.h"
  #ifdef SERVER
    swstat_t SWData;
  #endif
%}

%INTERFACE <SWData:DG/data>
%INTERFACE <subbus>

&command
  : Fail Light &fon_off * { set_failure($3); }
  : &SWTM * { if_SWData.Turf(); }
  ;
&SWTM
  : SW Status &swstat {
        SWData.SWStat = $3;
      }
#  : Laser System 1 has Failed { SWData.Laser_Status |= LS_1_FAILURE; }
#  : Laser System 2 has Failed { SWData.Laser_Status |= LS_2_FAILURE; }
#  : Laser System 3 has Failed { SWData.Laser_Status |= LS_3_FAILURE; }
#  : Laser System 1 has Shutdown { SWData.Laser_Status |= LS_1_SHUTDOWN; }
#  : Laser System 2 has Shutdown { SWData.Laser_Status |= LS_2_SHUTDOWN; }
#  : Laser System 3 has Shutdown { SWData.Laser_Status |= LS_3_SHUTDOWN; }
#  : Pinch Valve Set Gain Gp &gain { SWData.PV_Gp = $6; }
#  : Pinch Valve Set Gain Gi &gain { SWData.PV_Gi = $6; }
#  : Cell Pressure Setpoint &gain { SWData.PV_SetP = $4; }
  ;
&swstat <int>
  : Set %d { $0 = $2; }
  : Altitude Takeoff { $0 = SWS_TAKEOFF; }
  : Altitude Climb { $0 = SWS_CLIMB; }
  : Altitude Descend { $0 = SWS_DESCEND; }
  : Altitude Land { $0 = SWS_LAND; }
  : Lamp Enable { $0 = SWS_H2O_ENABLE; }
  : Lamp Disable { $0 = SWS_H2O_DISABLE; }
  : Laser Start { $0 = SWS_DFB_START; }
  : Laser Stop { $0 = SWS_DFB_STOP; }
  : Laser Select HHH and Start { $0 = SWS_DFB_HHH; }
# : Bench Gas Close { $0 = SWS_BENCH_CLOSE; }
# : Bench Gas Pump/Purge { $0 = SWS_BENCH_PUMP_PURGE; }
# : Bench Gas PI { $0 = SWS_BENCH_PI; }
# : Bench Gas Gains Set { $0 = SWS_BENCH_GAINS; }
# : Bench Gas Fill Cell { $0 = SWS_BENCH_FILL_CELL; }
  : Time Warp { $0 = SWS_TIME_WARP; }
  : ReadFile { $0 = SWS_READFILE; }
  : Shutdown { $0 = SWS_SHUTDOWN; }
  ;
&fon_off <int>
  : on { $0 = 1; }
  : off { $0 = 0; }
  : other { $0 = 2; }
  : both { $0 = 3; }
  ;
# &gain <unsigned short>
#         : %lf ( xx.x ) {
#             double val = $1*10 + .5;
#             if ( val < 0 ) val = 0.;
#             else if ( val > 9999. ) val = 9999.;
#             $0 = (unsigned short)val;
#           }
#         ;
