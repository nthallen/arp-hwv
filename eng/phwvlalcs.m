function phwvlalcs(varargin);
% phwvlalcs( [...] );
% Lamp C Status
h = ne_dstat({
  'LampCS', 'DS844', 2; ...
	'LampCDS', 'DS822', 2; ...
	'ChopCDS', 'DS824', 11 }, 'Status', varargin{:} );
