function phwvhhhsspovf(varargin);
% phwvhhhsspovf( [...] );
% SSP OVF
h = ne_dstat({
  'CAOVF1', 'SSP_Flags', 0; ...
	'CAOVF2', 'SSP_Flags', 1; ...
	'CAOVF3', 'SSP_Flags', 2; ...
	'PAOVF1', 'SSP_Flags', 3; ...
	'PAOVF2', 'SSP_Flags', 4; ...
	'PAOVF3', 'SSP_Flags', 5; ...
	'ADOVF1', 'SSP_Flags', 6; ...
	'ADOVF2', 'SSP_Flags', 7; ...
	'ADOVF3', 'SSP_Flags', 8 }, 'OVF', varargin{:} );
