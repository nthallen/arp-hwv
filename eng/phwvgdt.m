function phwvgdt(varargin);
% phwvgdt( [...] );
% Gas Deck Temp
h = timeplot({'A_RgT'}, ...
      'Gas Deck Temp', ...
      'Temp', ...
      {'A\_RgT'}, ...
      varargin{:} );
