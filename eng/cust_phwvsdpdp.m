function cust_phwvsdpdp(h)
% cust_phwvsdpdp(h)
% Customize plot created by phwvsdpdp

% phwvsdpdp's definition:

% function phwvsdpdp(varargin);
% % phwvsdpdp( [...] );
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
