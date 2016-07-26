function cust_phwviwg1_iwg1_stattd(h)
% cust_phwviwg1_iwg1_stattd(h)
% Customize plot created by phwviwg1_iwg1_stattd

% phwviwg1_iwg1_stattd's definition:

% function phwviwg1_iwg1_stattd(varargin);
% % phwviwg1_iwg1_stattd( [...] );
% % IWG1 Stat T Drift
% h = timeplot({'TDDrift','TDrift'}, ...
%       'IWG1 Stat T Drift', ...
%       'T Drift', ...
%       {'TDDrift','TDrift'}, ...
%       varargin{:} );

% Example customizations include:
%   set(h,'LineStyle','none','Marker','.');
Y = get(h(2),'YData');
Y(abs(Y) > 200) = NaN;
set(h(2),'YData', Y);
set(h,'LineStyle','none','Marker','.');