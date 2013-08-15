function cust_phwvhhhspvp(h)
% cust_phwvhhhspvp(h)
% Customize plot created by phwvhhhspvp

% phwvhhhspvp's definition:

% function phwvhhhspvp(varargin);
% % phwvhhhspvp( [...] );
% % SPV P
% h = timeplot({'SPV_P'}, ...
%       'SPV P', ...
%       'P', ...
%       {'SPV\_P'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
ydata = get(h,'YData')';
ydataf = fmedianf(ydata,4);
set(h,'YData',ydataf);
