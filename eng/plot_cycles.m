function plot_cycles
% plot_cycles
runsdir = ne_load_runsdir('HWV_Data_Dir');
ifile = [ runsdir filesep getrun(1) filesep 'hwveng_8.mat' ];
hw8 = load(ifile);
ifile = [ runsdir filesep getrun(1) filesep 'lyamrcat.mat' ];
CC = load(ifile);
tcat = time2d(CC.Tlyamrcat);
cat = CC.cat;
[tcat,I] = sort(tcat);
cat = cat(I);
t = time2d(hw8.Thwveng_8);
PMT = hw8.PMTA_Counts;
UVA = hw8.UVA1_Counts;
% v = bitand(hw8.Ct0Stat,32768) == 0 & bitand(hw8.Ct1Stat,32768) == 0;
% t = t(v);
% PMT = PMT(v);
% UVA = UVA(v);
if length(t) ~= length(tcat)
    if length(t)+1 == length(tcat)
        tcat = tcat(1:end-1);
        cat = cat(1:end-1);
    else
        error('length(cat) != length(t8)');
    end
end
    
v0 = cat == 0;
v1 = cat == 1;
v2 = cat == 2;
v3 = cat == 3;
v4 = cat == 4;
figure; plot(tcat,PMT,'k', ...
    tcat(v0),PMT(v0),'y.', ...
    tcat(v3),PMT(v3),'b.', ...
    tcat(v1),PMT(v1),'g.', ...
    tcat(v2),PMT(v2),'r.', ...
    tcat(v4),PMT(v4),'m*');
title(sprintf('PMTA: %s', getrun));
legend('cycle','init','transition','fg','bg','discard');
figure; plot(tcat,UVA,'k', ...
    tcat(v0),UVA(v0),'y.', ...
    tcat(v3),UVA(v3),'b.', ...
    tcat(v1),UVA(v1),'g.', ...
    tcat(v2),UVA(v2),'r.', ...
    tcat(v4),UVA(v4),'m*');
title(sprintf('UVA1: %s', getrun));
legend('cycle','init','transition','fg','bg','discard');
