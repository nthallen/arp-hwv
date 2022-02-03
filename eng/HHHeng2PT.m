function HHHeng2PT(lab)
%This is a customized eng to PT file conversion program for HCI and HHH.
%This creates the PT.mat file required by the ICOSfit programs.
if nargin < 1
  lab = 0;
end
cfg = load_ICOSfit_cfg;
runs = ne_load_runsdir('HWV_Data_Dir');
run = getrun(1);
E1 = load_eng('hwveng_1.mat', runs, run);
E8 = load_eng('hwveng_8.mat', runs, run);
if isempty(E1) || isempty(E8)
    return;
end
T1 = E1.Thwveng_1;
T8 = E8.Thwveng_8;

if strcmp(cfg.ScanDir,'SSPo')
    PT.TPT = T1;
    PT.CellP = interp1(T8,E8.HHH1P*201.5121-5.6440+1.5,T1,'linear'); %cell pressure (in Torr) to use for fit
    % Note 1.5 added to zero on April 6, 2013!
    % PT.Tavg = interp1(T8,273.15 + (E8.HHH1T + E8.HHH2T)/2,T1,'linear'); %gas temp (in K) to use for fit
    PT.Tavg = interp1(T8,273.15 + E8.HHH1T*0.96228783 + 2.06939487,T1,'linear'); %gas temp (in K) to use for fit
    PT.ScanNum = E1.SSP_Num;
    PT.QCLI_Wave = E1.QCLI_Wave;
else
    PT.TPT = T1;
    T8m = movmean(T8,8);
    if lab
      PT.CellP = intermp1(T8m, movmean(E8.LFT_P,8)/2, T1,'nearest');
    else
      % PT.CellP = E8.HHH1P*201.5121-8.544; %cell pressure (in Torr) to use for fit 7/2013
      P = (E8.HHH1P + 0.0086).*248.7302;
      PT.CellP = interp1(T8m,movmean(P,8),T1,'nearest');
    end
    % Note 1.5 added to zero on April 6, 2013!
    % PT.Tavg = interp1(T8,273.15 + (E8.HHH1T + E8.HHH2T)/2,T1,'linear'); %gas temp (in K) to use for fit
    % PT.Tavg = 273.15 + E8.HHH1T*0.96228783 + 2.06939487; %gas temp (in K) to use for fit
    T = 273.15 + (E8.HHH1T+E8.HHH2T)/2; % Uncalibrated 7/2013
    PT.Tavg = interp1(T8m, movmean(T,8), T1, 'nearest');
    PT.ScanNum = E1.SSP_Num;
    PT.QCLI_Wave = E1.QCLI_Wave;
end
save PT.mat -STRUCT PT

function E = load_eng(base, runs, run)
file = base;
if ~exist(file, 'file')
    file = [runs '/' run '/' file];
end
if exist(file, 'file')
    E = load(file);
else
    fprintf(1,'Unable to locate engineering data file "%s"\n', base);
    E = [];
end
