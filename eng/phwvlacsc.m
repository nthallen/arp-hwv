function phwvlacsc(varargin);
% phwvlacsc( [...] );
% Ct Stat Ct 0
h = ne_dstat({
  'Resynch', 'Ct0Stat', 15; ...
	'L2Stat', 'Ct0Stat', 14; ...
	'Ovf16_4', 'Ct0Stat', 7; ...
	'Ovf16_3', 'Ct0Stat', 6; ...
	'Ovf16_2', 'Ct0Stat', 5; ...
	'Ovf16_1', 'Ct0Stat', 4; ...
	'Ovf20_4', 'Ct0Stat', 3; ...
	'Ovf20_3', 'Ct0Stat', 2; ...
	'Ovf20_2', 'Ct0Stat', 1; ...
	'Ovf20_1', 'Ct0Stat', 0 }, 'Ct 0', varargin{:} );
