function cust_phwvhhhhpvi(h)
% cust_phwvhhhhpvi(h)
% Customize plot created by phwvhhhhpvi

% phwvhhhhpvi's definition:

% function phwvhhhhpvi(varargin);
% % phwvhhhhpvi( [...] );
% % HPV I
% h = timeplot({'Las_I'}, ...
%       'HPV I', ...
%       'I', ...
%       {'Las\_I'}, ...
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
