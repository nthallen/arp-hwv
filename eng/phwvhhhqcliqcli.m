function phwvhhhqcliqcli(varargin);
% phwvhhhqcliqcli( [...] );
% QCLI QCLI s
h = ne_dstat({
  'QCLI_busy', 'QCLI_s', 15; ...
	'QCLI_cksum', 'QCLI_s', 14; ...
	'QCLI_cmderr', 'QCLI_s', 13; ...
	'QCLi_laser', 'QCLI_s', 12; ...
	'QCLI_cordte', 'QCLI_s', 11; ...
	'QCLI_ready', 'QCLI_s', 9; ...
	'QCLI_waveerr', 'QCLI_s', 8; ...
	'QCLI_dot', 'QCLI_s', 5; ...
	'QCLI_lot', 'QCLI_s', 4; ...
	'QCLI_loc', 'QCLI_s', 3; ...
	'QCLI_present', 'QCLI_CS', 11; ...
	'Cmd24DS', 'DS824', 8 }, 'QCLI s', varargin{:} );
