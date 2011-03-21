%INTERFACE <SoldrvA>
%INTERFACE <SoldrvB>
%INTERFACE <SoldrvC>

&command
  : Soldrv A Select Mode %d * { if_SoldrvA.Turf("S%d\n", $5); }
  : Soldrv B Select Mode %d * { if_SoldrvB.Turf("S%d\n", $5); }
  : Soldrv C Select Mode %d * { if_SoldrvC.Turf("S%d\n", $5); }
  ;
