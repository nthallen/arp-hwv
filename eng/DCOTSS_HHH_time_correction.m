function [Tout,ScanNum] = DCOTSS_HHH_time_correction
  % [Tout,ScanNum] = DCOTSS_time_correction
  % Determines appropriate time values for each ICOS scan number
  H1 = ne_load('hwveng_1','HWV_Data_Dir');
  T1 = H1.Thwveng_1;
  xi = (1:length(T1))';
  V = xi < 0; % all false
  if isfield(H1,'TDrift') && isfield(H1,'IWG1_Stale')
    V = xi>1 & H1.IWG1_Stale == 0;
  end
  if any(V)
    T1V = T1(V);
    TDrift = H1.TDrift(V);
    TDfitV = simple_fit(T1V-T1V(1),TDrift);
    TDfit = interp1(T1V,TDfitV,T1,'linear','extrap');
    % T1D = T1 - TDfit;
  else
    fprintf(1,'No TDrift in %s\n',getrun);
    TDfit = zeros(size(T1));
    % T1D = T1;
  end
  %%
  [~,ranges] = waves_used;
  rngs = {ranges.ranges};
  rngs = sort(vertcat(rngs{:}));
  for i = size(rngs,1):-1:1
    fprintf(1,'%d - %d\n', rngs(i,1),rngs(i,2));
    [T,SN] = TC_region(rngs(i,1), rngs(i,2), T1, TDfit);
    res(i) = struct('T',T,'SN',SN);
  end
  Tout = {res.T};
  Tout = vertcat(Tout{:});
  ScanNum = {res.SN};
  ScanNum = vertcat(ScanNum{:});
end
  %%
function [Tout,ScanNum] = TC_region(scan_start, scan_end, T1, TDfit)
  ssp = (scan_start:scan_end)';
  TS = scantime(ssp);
  N = round(1/mean(diff(TS)));
  T = round(TS*N); %time2d
  %%
  Tfit = simple_fit(ssp,(T-T(1))-(ssp-ssp(1)));
  T2 = ssp-ssp(1)+T(1)+Tfit;
  TDfit2 = interp1(T1*N,TDfit,T2);
  T2a = T2-TDfit2;
  T3 = round(T2a);
  figure;
  delta = -T(1)-ssp+ssp(1);
  h = plot(ssp,(T+delta)/N,ssp,(T2+delta)/N,ssp,(T2a+delta)/N,ssp,(T3+delta)/N);
  h(4).LineWidth = 3;
  title(sprintf('Time correction: %s', getrun));
  xlabel('Scan Number');
  ylabel(sprintf('T-Scan Number/%d sec',N));
  legend('scantime()','linear','IWG1','corrected','Location','SouthEast');
%%
  Nidx = find(diff(T3)<=0);
  if ~isempty(Nidx)
    T4 = T3;
    for i=1:length(Nidx)
      idx = Nidx(i);
      j = 0;
      while idx+j+1 <= length(T4) && T4(idx+j+1) <= T4(idx+j)
        T4(idx+j+1) = T4(idx+j)+1;
        j = j+1;
      end
    end
    T3 = T4;
  end
%%  
  if nargout > 0
    Tout = T3/N;
    if nargout > 1
      ScanNum = ssp;
    end
  end
end

function fit = simple_fit(X,Y)
  Y2 = stair_fit(X,Y);
  fit = Y2;
  dY2 = diff(Y2);
  adY2 = abs(dY2);
  breaks = [0;find(adY2>1);length(Y2)];
  for i = 1:length(breaks)-1
    start = breaks(i)+1;
    endreg = breaks(i+1);
    R = start:endreg;
    steps = find(dY2(start:endreg-1))+start-1;
    if ~isempty(steps)
      if length(steps) == 1
        V = polyfit(X(R),Y2(R),1);
        fit(R) = polyval(V,X(R));
      else % fit to verticals
        Xvals = (X(steps) + X(steps+1))/2;
        Yvals = (Y(steps) + Y(steps+1))/2;
        V = polyfit(Xvals,Yvals,1);
        fit(R) = polyval(V,X(R));
      end
    end % else fit = Y2
  end
end

function fit = stair_fit(X,Y)
  % This if for cases where Y is integral and drifting slowly with respect to
  % X. There may be oscillations when crossing an integer boundary, but
  % overall, the trend should be stepwise and monotonic. The output fit will
  % be linear with X.
  vals = unique(Y);
  if length(vals) == 1
    fit = Y;
  else
    V = polyfit(X,Y,1);
    increasing = V(1) > 0;
    % First eliminate any dithering, then fit between the vertical breaks
    % before = Y;
    start = 1;
    fit = Y;
    while start < length(fit)
      if increasing
        newval = min(fit(start:end));
      else
        newval = max(fit(start:end));
      end
      lastmatch = find(fit(start:end)==newval,1,'last') + start -1;
      fit(start:lastmatch) = newval;
      start = lastmatch+1;
    end
  end
end
