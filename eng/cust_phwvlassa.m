function cust_phwvlassa(h)
% cust_phwvlassa(h)
% Customize plot created by phwvlassa

% phwvlassa's definition:

% function phwvlassa(varargin);
% % phwvlassa( [...] );
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
