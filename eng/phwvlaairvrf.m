function phwvlaairvrf(varargin);
% phwvlaairvrf( [...] );
% A IRV RF
h = timeplot({'ARFBW','RFBWf','RFASt'}, ...
      'A IRV RF', ...
      'RF', ...
      {'BW','BWf','Set'}, ...
      varargin{:} );
