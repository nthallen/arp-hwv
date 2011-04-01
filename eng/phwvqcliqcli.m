function phwvqcliqcli(varargin);
% phwvqcliqcli( [...] );
% QCLI QCLI_s
h = ne_dstat({
  'Busy', 'QCLI_s', 15; ...
	'cksum', 'QCLI_s', 14; ...
	'cmderr', 'QCLI_s', 13; ...
	'laser', 'QCLI_s', 12; ...
	'InvCmd', 'QCLI_s', 11; ...
	'ready', 'QCLI_s', 9; ...
	'waveerr', 'QCLI_s', 8; ...
	'dot', 'QCLI_s', 5; ...
	'lot', 'QCLI_s', 4; ...
	'loc', 'QCLI_s', 3 }, 'QCLI_s', varargin{:} );
