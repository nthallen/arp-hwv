function HHHeng2PT
%This is a customized eng to PT file conversion program for HCI and HHH.
%This creates the PT.mat file required by the ICOSfit programs.
cfg = load_ICOSfit_cfg;
run = getrun(1);
E = load_eng('hwveng_1.mat', cfg, run);
E8 = load_eng('hwveng_8.mat', cfg, run);
if isempty(E) || isempty(E8)
    return;
end
T1 = E.Thwveng_1;
T8 = E8.Thwveng_8;

if strcmp(cfg.ScanDir,'SSPo')
    PT.TPT = T1;
    PT.CellP = interp1(T8,E8.HHH1P*201.5121-5.6440+1.5,T1,'linear'); %cell pressure (in Torr) to use for fit
    % Note 1.5 added to zero on April 6, 2013!
    % PT.Tavg = interp1(T8,273.15 + (E8.HHH1T + E8.HHH2T)/2,T1,'linear'); %gas temp (in K) to use for fit
    PT.Tavg = interp1(T8,273.15 + E8.HHH1T*0.96228783 + 2.06939487,T1,'linear'); %gas temp (in K) to use for fit
    PT.ScanNum = E.SSP_Num;
    PT.QCLI_Wave = E.QCLI_Wave;
else
    fprintf(1,'Unable to identify instrument from ScanDir "%s"\n', ...
        cfg.ScanDir);
    return;
end
save PT.mat -STRUCT PT

function E = load_eng(base, cfg, run)
file = base;
if ~exist(file, 'file')
    file = [cfg.Matlab_Path '/' run '/' file];
end
if exist(file, 'file')
    E = load(file);
else
    fprintf(1,'Unable to locate engineering data file "%s"\n', base);
    E = [];
end
