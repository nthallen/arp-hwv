function phwvlas(varargin);
% phwvlas( [...] );
% Lamp A Status
h = ne_dstat({
  'LampAS', 'DS844', 7; ...
	'LampADS', 'DS822', 7; ...
	'ChopADS', 'DS824', 9 }, 'Status', varargin{:} );
