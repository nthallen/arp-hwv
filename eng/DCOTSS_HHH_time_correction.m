function [Tout,ScanNum] = DCOTSS_HHH_time_correction
  % [Tout,ScanNum] = DCOTSS_time_correction
  % Determines appropriate time values for each ICOS scan number
  %%
  % Need a continuous range of ssp values
  [wvs,ranges] = waves_used;
  wvi = find([wvs.ISICOS]);
  ranges = ranges(wvi).ranges;
  if size(ranges,1) > 1
    warning('More than one range for waveform %s', wvs(wvi).Name);
  end
  ssp = (ranges(1):ranges(2))';
  TS = scantime(ssp);
  N = 10; % Hz
  T = round(TS*N); %time2d
  %%
  % Look at IWG1 correction
  H1 = ne_load('hwveng_1','HWV_Data_Dir');
  T1 = H1.Thwveng_1*N;
  V = T1 >= T(1) & T1 <= T(end);
  T1V = T1(V);
  if isfield(H1,'TDrift')
    TDrift = H1.TDrift - H1.IWG1_Stale;
    TDrift = TDrift(V);
    TDfit = simple_fit(T1V-T1V(1),TDrift);
  else
    fprintf(1,'No TDrift in %s\n',getrun);
    TDfit = zeros(size(T1V));
  end
  
  Tfit = simple_fit(ssp,(T-T(1))-ssp);
  T2 = ssp+T(1)+Tfit;
  TDfit2 = interp1(T1V,TDfit,T2);
  T2a = T2-TDfit2;
  T3 = round(T2a);
  figure;
  T0 = T(1)-time2d(T(1));
  h = plot(ssp,T-T0-ssp,ssp,T2-T0-ssp,ssp,T2a-T0-ssp,ssp,T3-T0-ssp);
  h(4).LineWidth = 3;
  title(sprintf('Time correction: %s', getrun));
  xlabel('Scan Number');
  ylabel('T-Scan Number');
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
