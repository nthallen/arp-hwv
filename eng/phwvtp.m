function phwvtp(varargin);
% phwvtp( [...] );
% Throttle Pot
h = timeplot({'TVPos'}, ...
      'Throttle Pot', ...
      'Pot', ...
      {'TVPos'}, ...
      varargin{:} );
