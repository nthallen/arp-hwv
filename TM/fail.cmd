# subbus INTERFACE requests subbus driver to terminate on quit.
# Not required if subbus is started in rc.local
%INTERFACE <subbus>

&command
  : Fail Light &fon_off * { set_failure($3); }
  ;
&fon_off <int>
  : on { $0 = 1; }
  : off { $0 = 0; }
  : other { $0 = 2; }
  : both { $0 = 3; }
  ;
