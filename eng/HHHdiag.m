%% HHH to Lyman-alpha intercomparison
% Load lyamreng.mat, specified HHH fit, plot relative differences
% as a function of various things
% I can derive the relative difference from committed data, but
% I need engineering data for the pressures:
%   SPV pressure: thwv1,hwv1.SPV_P passed through a small median filter
%   Duct pressure: thwv8,hwv8.HHH1P * 201.512098 -5.64399177
%   Ambient pressure: merge.UTC,merge.PRESSURE
%% Look for committed data
arc = 'C:\Data\HWV\SEAC4RS\Archive';
need_Pamb = 0;
do_multiplot = 0;
day = getrun(1);
n = find(day == '.',1);
day = day(1:n-1);
if strcmp(day,'130831')
    day = '130830';
end
pat = [arc filesep 'SEAC4RS-HWV-H2O_ER2_20' day '_R*.ict'];
files = dir(pat);
if length(files) ~= 1
    error('Could not find any or unique archive for run %s', day);
end
a = load_seac4rs_merge([ arc filesep files.name ]);
v = a.H2O_HHH > 0 & a.H2O_LYA > 0;
tlya = a.Time_UTC(v);
% lyaf = fmedianf(a.H2O_LYA(v),2);
lyaf = a.H2O_LYA(v);
lyafh = lyaf;
thhh = tlya;
chi = a.H2O_HHH(v);
%--- This code is for using lyamreng.mat and ICOSout.R1.3p
% [lya,tlya] = ne_load('lyamreng', 'HWV_Data_Dir');
% base = 'ICOSout.R1.3p';
% [chi,scans,Phhh] = mixlines(base,4);
% chi = chi * 1e6; % switch to ppm
% thhh = time2d(scantime(scans));
% mhhh = (thhh-thhh(1))/60;
% lyaf = fmedianf(lya.h2o_lya_ppm, 10);
% lyafh = interp1(tlya,lyaf,thhh,'linear');
% Phhh0 = Phhh;
% thhh0 = thhh;
%% Look for merge data for ambient pressure
if need_Pamb
    pat = [arc filesep 'SEAC4RS-mrg01-ER2_merge_20' day '_R*.ict'];
    files = dir(pat);
    if length(files) ~= 1
        error('Could not find any or unique merge archive for run %s', day);
    end
    b = load_seac4rs_merge([ arc filesep files.name ]);
    tPamb = b.UTC;
    Pamb = b.PRESSURE * 760 / 1013.25; % Torr
end
[hwv1,thwv1] = ne_load('hwveng_1', 'HWV_Data_Dir');
[hwv8,thwv8] = ne_load('hwveng_8','HWV_Data_Dir');
%%
%Phhh = interp1(thhh0,Phhh0,thhh);
[hwv8,thwv8] = ne_load('hwveng_8','HWV_Data_Dir');
Pduct = interp1(thwv8,hwv8.HHH1P,thhh) * 201.512098 -5.64399177; % Torr
%% Calculate relative difference
RD = 100*(chi-lyafh)./lyafh; % percent difference from Ly-a
Pspv = hwv1.SPV_P;
Pspv(isnan(Pspv)) = -1;
Pspv = fmedianf(Pspv,1);
dP_duct_spv = interp1(thwv1,Pspv,thhh,'linear','extrap')-Pduct;
if need_Pamb
    dP_amb_spv = interp1(thwv1,Pspv,thhh,'linear','extrap') - interp1(tPamb,Pamb,thhh);
end
%%
if do_multiplot
    % scatter(dP_duct_spv, RD, 2, mhhh);
    N = 4;
    ax = nsubplots(N);
    semilogy(ax(1),tlya, lyaf, thhh, chi); legend(ax(1),'Ly-\alpha','HHH');
    plot(ax(2),tlya,RD);
        ylabel(ax(2),'RD');
    if need_Pamb
        plot(ax(3),tPamb,Pamb,thhh,Pduct,thwv1,Pspv);
            legend(ax(3),'Pamb','Pduct','Pspv');
        plot(ax(4),thhh,dP_duct_spv,thhh,dP_amb_spv);
            legend(ax(4),'spv-duct','spv-amb');
    else
        plot(ax(3),thhh,Pduct,thwv1,Pspv);
            legend(ax(3),'Pduct','Pspv');
        plot(ax(4),thhh,dP_duct_spv);
            legend(ax(4),'spv-duct');
    end
    title(ax(1),sprintf('Relative difference vs dP (spv-duct): %s', getrun));
    linkaxes(ax,'x');
    nsubplots(N,ax);
end

% figure; plot(dP_duct_spv, RD, '.');
% title(sprintf('Relative difference vs dP (spv-duct): %s', getrun));
% ylabel('HHH % difference from Ly-\alpha');
% xlabel('P_{spv} - P_{duct}');
% figure; plot(dP_amb_spv, RD,'.');
% title(sprintf('Relative difference vs dP (spv-amb): %s', getrun));
% ylabel('HHH % difference from Ly-\alpha');
% xlabel('P_{spv} - P_{amb}');
%%
maxDP = max(dP_duct_spv);
minDP = min(dP_duct_spv);
bins = minDP:10:maxDP;
binN = 1:length(bins);
bin = interp1(bins, binN, dP_duct_spv, 'nearest', 'extrap');
dPB = zeros(length(bins),1);
dPBstd = dPB;
RDB = zeros(length(bins),1);
RDBstd = RDB;
for i = binN
    v = bin==i;
    sN = sqrt(sum(v));
    dPv = dP_duct_spv(v);
    dPB(i) = mean(dPv);
    dPBstd(i) = std(dPv)/sN;
    RDv = RD(v);
    RDB(i) = mean(RDv);
    RDBstd(i) = std(RDv)/sN;
end
%%
figure;
ax = [ subplot(5,1,1) subplot(5,1,[2:5]) ];
plot(ax(1),thhh,dP_duct_spv);
title(ax(1),sprintf('dP (spv-duct): %s', getrun));
scatter(ax(2),dP_duct_spv, RD, 1, 'b');
hold(ax(2),'on');
errorbar(ax(2),dPB, RDB, RDBstd, 'xr');
plot(ax(2),dPB,RDB,'r');
title(ax(2),sprintf('Relative difference vs dP (spv-duct): %s', getrun));
ylabel(ax(2),'HHH % difference from Ly-\alpha');
xlabel(ax(2),'P_{spv} - P_{duct}');
ylim(ax(2),[-25 -5]);
xl = xlim(ax(2));
i = find(RDBstd < 0.5,1);
xl(1) = dPB(i);
xlim(ax(2),xl);
ylim(ax(1),xl);
