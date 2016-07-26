wv = waves_used;
if length(wv) ~= 1
    error('More than one waveform used');
end
SignalRegion = ...
    get_waveform_params( wv.Name, ...
      'SignalRegion', wv.TzSamples+100:wv.NetSamples-wv.TzSamples-20 );

[line_pos,S] = get_line_position('R2','5p');
PTE = load(S.PTEfile);
SN = S.scannum;
if size(PTE,2) > 16
    SNe = PTE(:,1);
    Xmax = SignalRegion(end);
    X0 = unique(PTE(:,4));
    XV = ((SignalRegion(end)-X0)*1e-3).^(3:-1:0)';
    PC = PTE(:,13:16);
    EtlnPwr = PC*XV;
end
LXV = (SignalRegion(end)*1e-3).^(0:S.n_base_params-1)';
LPC = S.fitdata(:,S.n_input_params+(1:S.n_base_params));
CellPwr = LPC*LXV;

figure;
ax = [ nsubplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3) ];
plot(ax(1),SN,CellPwr);
if size(PTE,2) > 16
    hold on;
    plot(ax(1),SNe,EtlnPwr);
    hold off;
end
ylabel(ax(1),'Cell Power');
set(ax(1),'xticklabel',[]);
plot(ax(2),SN,S.P); ylabel(ax(2),'Pressure');
set(ax(2),'YAxisLocation','right', 'xticklabel', []);% Pressure
plot(ax(3),SN,line_pos); ylabel(ax(3),'Line Pos');
linkaxes(ax,'x');

% figure; plot(S.P, CellPwr,'.');
% figure; plot(S.P, line_pos,'.');
%%
ccode = 'grcmyk';
rd = ne_load_runsdir('HWV_Data_Dir');
lya = load([rd filesep getrun(1) filesep 'lyamreng.mat']);
tlya = time2d(lya.Tlyamreng);
figure;
bx = [ nsubplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3) ];
plot(bx(1), tlya,lya.h2o_lya_ppm);
leg = {'Lyman-\alpha'};
fits = dir('ICOSout*');
hold(bx(1),'on');
for i=1:length(fits)
    [chi,scans] = mixlines(fits(i).name,4);
    chi = chi * 1e6;
    tchi = time2d(scantime(scans));
    plot(bx(1),tchi,chi,ccode(i));
    mri = interp1(tlya, lya.h2o_lya_ppm, tchi, 'nearest');
    plot(bx(2),tchi, (chi-mri)./mri, ccode(i));
    hold(bx(2),'on');
    plot(bx(3),tchi, chi-mri, ccode(i));
    hold(bx(3),'on');
    leg{end+1} = fits(i).name(9:end);
end
hold(bx(1),'off');
hold(bx(2),'off');
hold(bx(3),'off');
legend(bx(1),leg{:});
legend(bx(2),leg{2:end});
legend(bx(3),leg{2:end});
linkaxes(bx,'x');

