function cust_phwvlasdpdp(h)
% cust_phwvlasdpdp(h)
% Customize plot created by phwvlasdpdp

% phwvlasdpdp's definition:

% function phwvlasdpdp(varargin);
% % phwvlasdpdp( [...] );
% % SDP DP
% h = timeplot({'SDPDP'}, ...
%       'SDP DP', ...
%       'DP', ...
%       {'SDPDP'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);

set(h,'LineStyle','none','Marker','.');
ax = get(h,'parent');
set(ax,'ylim',[-.125 15]);
