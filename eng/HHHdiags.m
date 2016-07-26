function HHHdiags(varargin)
if isempty(varargin)
    varargin = {'130819.2F', '130821.2F', '130823.2F', '130827.2F' };
    % No archived LyA: '130831.1F'
    % Not fit yet , '130902.2F', '130904.5F', '130906.2F' };
end
fullscreen = [ 1          31        1280         920];
doprint = 0;
argN = 1;
while argN <= length(varargin)
    rundir = varargin{argN};
    timelim = [];
    if argN < length(varargin) && isnumeric(varargin{argN+1})
        timelim = varargin{argN+1};
        argN = argN+1;
    end
    argN = argN + 1;
    H = HHHanal(rundir, 'R1','3p', timelim);
    dP = H.Pspv - H.Pduct;
    Nd = 20;
    ddP = [ zeros(Nd,1); dP(Nd+1:end)-dP(1:end-Nd) ];
    bins = min(dP):10:max(dP);
    [mRD,sRD] = bin_average(bins, dP, H.RD);
    [mdP,sdP] = bin_average(bins, dP, dP);
    [mPS,sPS] = bin_average(bins, dP, H.PwrSig);
    PR = H.PwrSig./H.PwrEtln;
    [mPR,sPR] = bin_average(bins, dP, PR);
    [mPE,sPE] = bin_average(bins,dP,H.PwrEtln);

    figure;
    ax = [ nsubplot(5, 1, [3 2], 1) ...
    nsubplot(5, 1, [5 2], 1) nsubplot(9, 1, 1, 1) ];
    scatter(ax(3),fastavg(H.T,10),fastavg(dP,10),4,fastavg(ddP,10));
    ylabel(ax(3),'Pspv - Pduct');
    scatter(ax(2),fastavg(dP,10),fastavg(H.PwrSig,10),4,fastavg(ddP,10));
    hold(ax(2),'on');
    plot(ax(2),mdP,mPS,'r');
    errorbar(ax(2),mdP,mPS,sPS,'r');
    ylabel(ax(2),'Sig Power');
    scatter(ax(1),fastavg(dP,10),fastavg(H.RD,10),4,fastavg(ddP,10));
    hold(ax(1),'on');
    plot(ax(1),mdP,mRD,'r');
    errorbar(ax(1),mdP,mRD,sRD,'r');
    title(ax(1),sprintf('Relative difference versus dP: %s', rundir));
    ylabel(ax(1),'Relative Diff');
    nsubplots(2,ax(1:2));
    xlabel(ax(2),'Pspv - Pduct');
    colorbar('west','peer',ax(2));
    linkaxes(ax(1:2),'x');

    % Save as png
    if doprint
        oldpos = get(gcf,'position');
        set(gcf,'position',fullscreen);
        print(gcf, '-dpng', ['RDcompare/RD_DP_' rundir '.png']);
        set(gcf,'position',oldpos);
        delete(gcf);
    end
    
    ax = nsubplots(2);
    scatter(ax(2),fastavg(dP,10),fastavg(H.PwrEtln,10),4,fastavg(ddP,10));
    hold(ax(2),'on');
    plot(ax(2),mdP,mPE,'r');
    errorbar(ax(2),mdP,mPE,sPE,'r');
    ylabel(ax(2),'Etln Pwr');
    colorbar('west','peer',ax(2));
    scatter(ax(1),fastavg(dP,10),fastavg(H.PwrSig,10),4,fastavg(ddP,10));
    hold(ax(1),'on');
    plot(ax(1),mdP,mPS,'r');
    errorbar(ax(1),mdP,mPS,sPS,'r');
    title(ax(1),sprintf('Power versus dP: %s', rundir));
    ylabel(ax(1),'Sig Pwr');
    nsubplots(2,ax);
    xlabel(ax(2),'Pspv - Pduct');
    linkaxes(ax,'x');

    if doprint
        oldpos = get(gcf,'position');
        set(gcf,'position',fullscreen);
        print(gcf, '-dpng', ['RDcompare/Pwr_DP_' rundir '.png']);
        set(gcf,'position',oldpos);
        delete(gcf);
    end
    
%     figure;
%     ax = [ subplot(5,1,1) subplot(5,1,[2:5]) ];
%     plot(ax(1),H.T,dP);
%     title(ax(1),sprintf('dP (spv-duct): %s', rundir));
%     scatter(ax(2),fastavg(dP,10), fastavg(H.PwrSig,10),2,fastavg(ddP,10));
%     colorbar;
%     title(ax(2),sprintf('Signal Power vs dP colored by d(dP)/dT: %s', rundir));
%     ylabel(ax(2),'Sig Pwr');
%     xlabel(ax(2),'Pspv - Pduct');
end
