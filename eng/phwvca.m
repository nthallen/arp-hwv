function phwvca(varargin);
% phwvca( [...] );
% Current Air
h = timeplot({'AirA_I','AirB_I'}, ...
      'Current Air', ...
      'Air', ...
      {'AirA','AirB'}, ...
      varargin{:} );