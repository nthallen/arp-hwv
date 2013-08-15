function cust_phwvhhhspvt(h)
% cust_phwvhhhspvt(h)
% Customize plot created by phwvhhhspvt

% phwvhhhspvt's definition:

% function phwvhhhspvt(varargin);
% % phwvhhhspvt( [...] );
% % SPV T
% h = timeplot({'SPV1T','SPV2T','SPV_T1C','SPV_T2C'}, ...
%       'SPV T', ...
%       'T', ...
%       {'SPV1T','SPV2T','SPV\_T1C','SPV\_T2C'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
for i = [1 2]
    ydata = get(h(i),'YData')';
    ydataf = fmedianf(ydata,1);
    set(h(i),'YData',ydataf);
end
