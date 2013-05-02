function cust_phwvssa(h)
% cust_phwvssa(h)
% Customize plot created by phwvssa

% phwvssa's definition:

% function phwvssa(varargin);
% % phwvssa( [...] );
% % Sol St A
% h = timeplot({'SolStA'}, ...
%       'Sol St A', ...
%       'A', ...
%       {'SolStA'}, ...
%       varargin{:} );

% Example customizations include:
set(h,'LineStyle','none','Marker','.');
%   ax = get(h(1),'parent');
%   set(ax,'ylim',[0 800]);
