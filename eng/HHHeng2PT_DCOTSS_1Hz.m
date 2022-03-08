function HHHeng2PT_DCOTSS_1Hz
%This is a customized eng to PT file conversion program for HCI and HHH.
%This creates the PT.mat file required by the ICOSfit programs.
%cfg = load_ICOSfit_cfg;
runs = ne_load_runsdir('HWV_Data_Dir');
run = getrun(1);
E1 = load_eng('hwveng_1.mat',runs,run);
E8 = load_eng('hwveng_8.mat',runs,run);
% load('fltdate.mat')
fltdate = 210401;
if isempty(E1) || isempty(E8)
    return;
end
T1 = E1.Thwveng_1;
T8 = E8.Thwveng_8;

if fltdate<210000
else
    PT.TPT = T1;
    %
    % PRESSURE in Torr
    % NOTE: Pressure plumbing "fixed" on 210721 
    %   - DP and HHH2P removed, HHH1P isolated
    % **HHH1P** measuring static pressure from Pitot Tube in duct
    %PT.CellP = interp1(fastavg(T8,8),fastavg((E8.HHH1P + 0.0169).*249.2489,8),...
    %    T1,'nearest');                              % Post-DCOTSS Prs. Cal. 211214 
    PT.CellP = interp1(fastavg(T8,8),fastavg((E8.HHH1P + 0.0086).*248.7302,8),...
        T1,'nearest');                              % DCOTSS Prs. Cal. 210721 
    %PT.CellP = interp1(fastavg(T8,8),fastavg((E8.HHH2P - 0.0192).*201.5686,8),...
    %    T1,'nearest');                              % SEAC4RS Cal.
    %
    % **HHH2P** measuring static pressure in HHH prs. assy. box (!)
    % PT.CellP = interp1(fastavg(T8,8),fastavg((E8.HHH2P - 0.1721).*193.4335,8),...
    %    T1,'nearest');                              % Post-DCOTSS Prs. Cal. 210721 
    % PT.CellP = interp1(fastavg(T8,8),fastavg((E8.HHH2P - 0.1723).*192.3339,8),...
    %    T1,'nearest');                              % DCOTSS Prs. Cal. 210721 
    %
    % TEMPERATURE in K
    PT.Tavg = interp1(fastavg(T8,8),fastavg(273.15 + (E8.HHH1T + E8.HHH2T)./2,8),...
        T1,'nearest');
    % PT.Tavg = 273.15 + E8.HHH1T*0.96228783 + 2.06939487; 
    %
    % SCANS
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
