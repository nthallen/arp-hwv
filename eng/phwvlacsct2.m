function phwvlacsct2(varargin);
% phwvlacsct2( [...] );
% Ct Stat Ct 2
h = ne_dstat({
  'Resynch', 'Ct2Stat', 15; ...
	'L2Stat', 'Ct2Stat', 14; ...
	'Ovf16_4', 'Ct2Stat', 7; ...
	'Ovf16_3', 'Ct2Stat', 6; ...
	'Ovf16_2', 'Ct2Stat', 5; ...
	'Ovf16_1', 'Ct2Stat', 4; ...
	'Ovf20_4', 'Ct2Stat', 3; ...
	'Ovf20_3', 'Ct2Stat', 2; ...
	'Ovf20_2', 'Ct2Stat', 1; ...
	'Ovf20_1', 'Ct2Stat', 0 }, 'Ct 2', varargin{:} );
