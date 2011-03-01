%INTERFACE <SoldrvA>

&command
  : Soldrv Select Mode %d * { if_SoldrvA.Turf("S%d\n", $4); }
  ;
