%INTERFACE <SSP>

%{

#ifdef SERVER
  #include "hsatod.h"
  #define QCLI_ICOS \
      (HSAD_OPT_A|HSAD_OPT_B|HSAD_OPT_C|HSAD_TRIG_3|HSAD_TRIG_RISING)

  hsatod_setup_t ssp_setup;

  static struct ssp_bd_s {
    hsatod_setup_t *setup;
    cmdif_rd *intf;
  } ssp_bd[1] = {
    { &ssp_setup, &if_SSP },
  };

#endif

%}


&command
  : &SSP Start * {
        hsatod_setup_t *setup = ssp_bd[$1].setup;
        if (setup->NAvg > 0) {
	  ssp_bd[$1].intf->Turf(
	   "DA NF:%ld NS:%d NA:%d NC:%d NE:%d "
	   "T%c:0 TS:%d A%c EN\n",
	   setup->FSample, setup->NSample/setup->NAvg,
	   setup->NAvg, setup->NCoadd,
	   setup->Options & 7,
	   (setup->Options & HSAD_TRIG_RISING) ? 'U' : 'D',
	   (setup->Options & HSAD_TRIG_3)/HSAD_TRIG_1,
	   (setup->Options & HSAD_TRIG_AUTO) ? 'E' : 'D' );
        } else nl_error(2, "SSP %d NAvg out of range", $1+1);
      }
  : &SSP Stop * { ssp_bd[$1].intf->Turf( "DA" ); }
  : &SSP Reset * { ssp_bd[$1].intf->Turf( "XR" ); }
  : &SSP Exit * { ssp_bd[$1].intf->Turf( "XX" ); }
  : &SSP Set NSample %ld (Number of Samples) * {
        ssp_bd[$1].setup->NSample = $4;
      }
  : &SSP Set FSample %ld (Raw Sample Frequency) * {
        ssp_bd[$1].setup->FSample = $4;
      }
  : &SSP Set NAvg %ld (Number of Consecutive Samples to Average) * {
        ssp_bd[$1].setup->NAvg = $4;
      }
  : &SSP Set NCoadd %d (Number of Scans to Coadd) * {
        ssp_bd[$1].setup->NCoadd = $4;
      }
  : &SSP Set Trigger &Trigger * {
          nl_error( 0, "Set trigger command: '%s'", $4 );
          ssp_bd[$1].intf->Turf( $4 );
      }
  : &SSP Set Trigger Level %d (Enter Trigger Level) &TrigPolarity * {
          ssp_bd[$1].intf->Turf( "%s:%d\n", $6, $5 );
      }
  : &SSP Logging &LogEnable * { ssp_bd[$1].intf->Turf( $3 ); }
  ;

# &SSP returns an index into ssp_bd[]
&SSP <int>
  : SSP { $0 = 0; }
  ;

&Trigger <const char *>
  : Source &TrigSource { $0 = $2; }
  : Auto { $0 = "AE\n"; }
  : NoAuto { $0 = "AD\n"; }
  ;

# TrigSource returns the appropriate trigger source string,
# which will be sent to sspdrv.
&TrigSource <const char *>
  : Channel 0 { $0 = "TS:0\n"; }
  : Channel 1 { $0 = "TS:1\n"; }
  : Channel 2 { $0 = "TS:2\n"; }
  : External { $0 = "TS:3\n"; }
  ;
&TrigPolarity <const char *>
  : Rising { $0 = "TU"; }
  : Falling { $0 = "TD"; }
  ;
&LogEnable <const char *>
  : Enable { $0 = "LE\n"; }
  : Disable { $0 = "LD\n"; }
  ;


&command
  : Select QCLI Waveform &QCLI_Wave * {
      *ssp_bd[0].setup = QCLI_Waves[$4];
      if_QCLI.Turf( "SW:%d\n", $4 );
    }
  ;
