function phwvhkhkps(varargin);
% phwvhkhkps( [...] );
% HK Power Status
h = ne_dstat({
  'PM0I1_S', 'PM0Stat', 0; ...
	'PM0I2_S', 'PM0Stat', 2; ...
	'PM0V1_S', 'PM0Stat', 1; ...
	'PM0V2_S', 'PM0Stat', 3; ...
	'PM0TO_S', 'PM0Stat', 4 }, 'Status', varargin{:} );
