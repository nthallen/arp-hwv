function phwvlalbs(varargin);
% phwvlalbs( [...] );
% Lamp B Status
h = ne_dstat({
  'LampBS', 'DS844', 0; ...
	'LampBDS', 'DS822', 0; ...
	'ChopBDS', 'DS824', 10 }, 'Status', varargin{:} );
