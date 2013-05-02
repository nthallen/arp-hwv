function HHHeng2PT
% HHHeng2PT
% Reads tildeeng_1.mat and creates a HHH-specific PT.mat appropriate
% for use with the icosfit utilities.
cfg = load_ICOSfit_cfg;
run = getrun(1);
PTin = load_eng('PT.mat', cfg, run);
if isempty(PTin)
    return;
end
PT.TPT = PTin.TPT;
PT.ScanNum = PTin.SSP_Num;
PT.QCLI_Wave = PTin.QCLI_Wave;
PT.CellP = PTin.HHH1P * 201.512098 - 5.64399177;
PT.Tavg = 0.96228783 * PTin.HHH1T + 2.06939487+273.15;
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
