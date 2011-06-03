function phwvsspstatus(varargin);
% phwvsspstatus( [...] );
% SSP Status
h = timeplot({'SSP_Status'}, ...
      'SSP Status', ...
      'Status', ...
      {'SSP\_Status'}, ...
      varargin{:} );
set(h,'LineStyle','none','Marker','.');
ax = get(h,'parent');
set(ax,'ylim',[-.125 4.125],'YTick',[0:4],'YTickLabel',...
    {'Gone','Connect','Ready','Armed','Trigger'});

