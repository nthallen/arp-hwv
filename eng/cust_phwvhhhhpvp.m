function cust_phwvhhhhpvp(h)
% cust_phwvhhhhpvp(h)
% Customize plot created by phwvhhhhpvp

% phwvhhhhpvp's definition:

% function phwvhhhhpvp(varargin);
% % phwvhhhhpvp( [...] );
% % HPV P
% h = timeplot({'HPV_P'}, ...
%       'HPV P', ...
%       'P', ...
%       {'HPV\_P'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
ax = get(h,'parent');
x = get(h,'XData');
ydata = get(h,'YData')';
ydataf = fmedianf(ydata,10);
set(h,'YData', ydataf);
yl = get(ax,'ylim');
set(h,'YData',ydata);
hold(ax,'on');
plot(ax,x,ydataf,'c');
hold(ax,'off');
set(ax,'ylim',yl);
