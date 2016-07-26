function H = HHHanal(rundir, region, suffix, timelim)
% H = HHHanal(rundir, region, suffix, timelim)
% Returns struct with
%  T: Time
%  LyA: [H2O]/[M] from Lyman Alpha
%  HHH: [H2O]/[M] from HHH
%  Pduct
%  Pspv
%  PwrEtln: Power at the etalon (from PTE.txt [saveall])
%  PwrSig: Output power (from baseline fit)
%
% LyA can be taken from submitted data or from lyamreng.mat
% HHH may as well come from a fit.
% The power numbers need to come from a fit
% We could use max power or power at the line position. May not matter.
% Pduct can come from fit.
% Pspv comes from engineering data
if nargin < 3
    suffix = '3p';
    if nargin < 2
        region = 'R1';
    end
end
curdir = cd(rundir);
[linepos,S] = get_line_position(region, suffix);
if size(linepos,2) > 1
    linepos = linepos(:,1);
end
PTE = load(S.PTEfile);
if size(PTE,2) < 18
    error('PTE file %s%s%s not generated using saveall 1', ...
        rundir, filesep, S.PTEfile);
end
SNe = PTE(:,1);
X0 = unique(PTE(:,4));
if length(X0) ~= 1
    error('X0 not constant in %s',S.PTEfile);
end
if length(SNe) ~= length(S.scannum) || ...
        any(SNe ~= S.scannum)
    error('%s: PTEfile is not perfect match to fit scans', rundir);
end
%%
XM = (((linepos-X0)*1e-3)*ones(1,4)).^(ones(size(linepos))*(3:-1:0));
if size(PTE,2) == 18
    PC = PTE(:,13:16);
elseif size(PTE,2) == 19
    PC = PTE(:,14:17);
else
    error('Unexpected ncols %d in PTEfile %s', size(PTE,2), S.PTEfile);
end
EtlnPwr = sum(PC.*XM,2);
%%
LXM = (((linepos-X0)*1e-3)*ones(1,S.n_base_params)).^(ones(size(linepos))*(0:S.n_base_params-1));
LPC = S.fitdata(:,S.n_input_params+(1:S.n_base_params));
CellPwr = sum(LPC.*LXM,2);
%%
arc = 'C:\Data\HWV\SEAC4RS\Archive';
day = getrun(1);
n = find(day == '.',1);
day = day(1:n-1);
if strcmp(day,'130831')
    day = '130830';
elseif strcmp(day,'130910')
    day = '130909';
end
pat = [arc filesep 'SEAC4RS-HWV-H2O_ER2_20' day '_R*.ict'];
files = dir(pat);
if length(files) ~= 1
    error('Could not find any or unique archive for run %s', day);
end
a = load_seac4rs_merge([ arc filesep files.name ]);
v = a.H2O_LYA <= 0;
a.H2O_LYA(v) = NaN;
tlya = a.Time_UTC;
%%
lya = a.H2O_LYA;
%%
Thhh = time2d(scantime(S.scannum));
lyah = interp1(tlya,lya,Thhh,'linear');
Chi = S.Chi * 1e6;
RD = 100*(Chi-lyah)./lyah; % percent difference from Ly-a
v = ~isnan(lyah);
%%
[hwv1,thwv1] = ne_load('hwveng_1', 'HWV_Data_Dir');
[hwv8,thwv8] = ne_load('hwveng_8','HWV_Data_Dir');
Pduct = interp1(thwv8,hwv8.HHH1P,Thhh) * 201.512098 -5.64399177; % Torr
Pspv = hwv1.SPV_P;
Pspv(isnan(Pspv)) = -1;
Pspv = fmedianf(Pspv,1);
dP_duct_spv = interp1(thwv1,Pspv,Thhh,'linear','extrap')-Pduct;
%%
if nargin >= 4 && ~isempty(timelim)
    v = v & Thhh > timelim(1) & Thhh < timelim(2);
end
%%
H.T = Thhh(v);
H.h2o_hhh = Chi(v);
H.h2o_lya = lyah(v);
H.RD = RD(v);
H.Pduct = Pduct(v);
H.Pspv = Pspv(v);
H.PwrEtln = EtlnPwr(v);
H.PwrSig = CellPwr(v);
%%
cd(curdir);
