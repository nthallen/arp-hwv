function cust_phwvhhhhpvlte(h)
% cust_phwvhhhhpvlte(h)
% Customize plot created by phwvhhhhpvlte

% phwvhhhhpvlte's definition:

% function phwvhhhhpvlte(varargin);
% % phwvhhhhpvlte( [...] );
% % HPV LTE
% h = timeplot({'LTE1R4T'}, ...
%       'HPV LTE', ...
%       'LTE', ...
%       {'LTE1R4T'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
ax = get(h,'parent');
x = get(h,'XData');
ydata = get(h,'YData')';
ydataf = fmedianf(ydata,10);
set(h,'YData',ydataf);
yl = ylim(ax);
set(h,'YData',ydata);
hold(ax,'on');
plot(ax,x,ydataf,'c');
hold(ax,'off');
set(ax,'ylim',yl);
