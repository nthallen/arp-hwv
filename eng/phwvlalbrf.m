function phwvlalbrf(varargin);
% phwvlalbrf( [...] );
% Lamp B RF
h = timeplot({'BRFBW','BRFFW','RFBSt','RFCSt'}, ...
      'Lamp B RF', ...
      'RF', ...
      {'BW','FW','RFBSt','RFCSt'}, ...
      varargin{:} );
