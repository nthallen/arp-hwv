function cust_phwvlasdpp(h)
% cust_phwvlasdpp(h)
% Customize plot created by phwvlasdpp

% phwvlasdpp's definition:

% function phwvlasdpp(varargin);
% % phwvlasdpp( [...] );
% % SDP P
% h = timeplot({'SD_HP','SD_LP','UVB1_Counts'}, ...
%       'SDP P', ...
%       'P', ...
%       {'SD\_HP','SD\_LP','UVB1\_Counts'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
cts = get(h(3),'YData');
set(h(3), 'YData', cts * 0.079376 - 4.98674);
hp = get(h(1),'YData');
set(h(1),'YData', hp * 0.998543 - 5.1434);