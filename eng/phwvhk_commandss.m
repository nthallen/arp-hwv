function phwvhk_commandss(varargin);
% phwvhk_commandss( [...] );
% Commands S
h = ne_dstat({
  'Cmd1S', 'DS844', 1; ...
	'Cmd3S', 'DS844', 3; ...
	'Cmd4S', 'DS844', 4; ...
	'Cmd5S', 'DS844', 5; ...
	'MZ1S', 'DS844', 6; ...
	'MZ2S', 'DS844', 8; ...
	'Cmd9S', 'DS844', 9; ...
	'MZ3S', 'DS844', 10; ...
	'MZ4S', 'DS844', 11; ...
	'Cmd12S', 'DS844', 12; ...
	'Cmd13S', 'DS844', 13; ...
	'Cmd14S', 'DS844', 14; ...
	'Cmd15S', 'DS844', 15 }, 'S', varargin{:} );
