%INTERFACE <icosfitd>

&command
  : icosfit &icosfit_cmd
  ;

&icosfit_cmd
  : Scan %ld (Scan Number) %f (Pressure in Torr) %f (Temperature in Kelvin) * {
        if_icosfitd.Turf("S:%ld,%f,%f\n", $2, $3, $4);
      }
  : PTE params %s * { if_icosfitd.Turf("P:%s\n", $3); }
  : Quit * { if_icosfitd.Turf("Q\n"); }
  ;
