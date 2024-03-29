%%
regen_PTE = false;
PTEref = '../PTEref.txt';
PTE = load(PTEref);
PTE_params = PTE(1,4:end);
clear PTE;
%
% First revert to the default
switch_scansdir('SSP');
[wvs,ranges] = waves_used;
if isempty(ranges)
  error('No scan data found');
elseif length(ranges) > 2
  error('More than two waveforms used');
end
%
% Now sort the ranges
for i=1:length(ranges)
  if size(ranges(i).ranges,1) ~= 1
    error('Range for %s has %d rows', wvs(ranges(i).wvno).Name, size(ranges(i).ranges,1));
  end
end
r = [ranges.ranges];
r = r(1:2:end);
[~,I] = sort(r);
for region = 1:length(I)
  wvno = ranges(I(region)).wvno;
  wvname = wvs(I(region)).Name;
  range = ranges(I(region)).ranges;
  fprintf(1,'Region %d: %s %d-%d\n', region, wvname, range);
  if strcmp(wvname,'HHH_10Hz')
    Rnum = region + 10;
  else
    Rnum = region;
  end
  PTEfile = sprintf('PTE_gen_R%d.txt',Rnum);
  if ~regen_PTE && exist(PTEfile,'file')
    fprintf(1,'Skipping PTE_gen %s\n', PTEfile);
  else
    if exist(PTEfile,'file')
      PTE = load(PTEfile);
      range = PTE([1 end],1);
    else
      range = get_starting_scan(Rnum, range);
    end
    fprintf(1,'Generate %s over %d-%d\n', PTEfile, range);
    scans = range(1):range(2);
    PTE_gen(scans, PTEfile,PTE_params);
  end
  if strcmp(wvname,'HHH_10Hz')
    Rnum = region;
    Rtxt = sprintf('R%d',Rnum);
    oPTEfile = sprintf('PTE_gen_%s.txt', Rtxt);
    if ~regen_PTE && exist(oPTEfile,'file')
      fprintf(1,'Skipping average_spectra\n');
    else
      fprintf(1,'average_spectra2(1,''%s'',''%s'')\n',PTEfile,oPTEfile);
      average_spectra2(1, PTEfile, oPTEfile);
    end
    switch_scansdir('SSP.average1');
    setup_icosfit(Rtxt, oPTEfile);
    switch_scansdir('SSP');
  else
    Rtxt = sprintf('R%d',Rnum);
    setup_icosfit(Rtxt, PTEfile)
  end
end
%%
% At this point, fitting can commence on R1 and/or R2
% We need to evaluate nu_F0 to see if we stayed online, so we'll do
% PTE_add_nu_F0() and then can plot nu_F0 to see if it looks good.
% If it doesn't and until it does, we need to go back, interpolate
% through back regions and try to fit again.
%
% Once that is OK, if there is a PTE_gen_R1[12].txt that goes with
% this, we can PTE_add_nu_F0() to interpolate on it and then
% setup_icosfit() with the added tweak that PTEfile gets '+ nu_F0'
% 
%%
% Take a first look to see how things went
%mixlines(base);
%f = gcf;
%f.Position(1) = 1400-f.Position(3);
S = ICOS_setup(base);
figure; 
ax = [ nsubplot(2,1,1) nsubplot(2,1,2) ];
plot(ax(1),S.scannum, S.Chi*1e6);
ax(1).YLim = [0 25];
ylabel(ax(1),'H_2O ppm');
ax(1).YAxisLocation = 'right';
ax(1).XTickLabel = [];
title(ax(1), getrun);
plot(ax(2),S.scannum, S.nu_F0);
ylabel(ax(2),'\nu_{F0}');
linkaxes(ax,'x');
%%
% Closer look: Want to see Chi, nu_F0 and floating: nu_F0
S = ICOS_setup(base);
figure;
ax = [nsubplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3)];
plot(ax(1),S.scannum,S.Chi * 1e6);
ax(1).YLim = [ 0 25 ];
ylabel(ax(1),'H_2O ppm');
ax(1).YAxisLocation = 'right';
ax(1).XTickLabel = [];
title(ax(1),getrun);
plot(ax(2),S.scannum,S.nu_F0);
ylabel(ax(2),'\nu_{F0}');
plot(ax(3),S.scannum,S.fitdata(:,S.float_cols(1+1)));
linkaxes(ax,'x');
%%
PTE_add_nu_F0(base,'ifile','PTE_gen_R11.txt');
%
setup_icosfit('R11','PTE_gen_R11_nu.txt');
%%
% Do whatever we have to to fixup the 1 Hz fit, starting with:
PTE_add_nu_F0(base);
% And then trying to interpolate through regions where we lost the line
%%
% Now to the 10Hz fit:
PTE10nu = PTE_add_nu_F0(base,'ifile','PTE_gen_10Hz.txt');
PTE = load(PTE10nu);
fitline('update_regions','R1',PTE([1 end],1));
clear PTE
%%
edit_ICOSfit_cfg; % To switch back to 10Hz scans
fitline
%%
fitfile = 'icosfit.R1.10Hz5p3er';
icosfit_reconfig(fitfile, '', ...
  'Verbosity', '2', ...
  'MaxEnsembleDriftPerScan', '5e-3 cm-1', ...
  'MaxIterations', '20', ...
  'PTEFile',[PTE10nu ' + nu_F0']);
%%
% No fit at 10 Hz
%%
function new_range = get_starting_scan(Rnum, range)
  ScansFile = sprintf('Scans_R%d.txt', Rnum);
  if exist(ScansFile,'file')
    SF_range = load(ScansFile);
    if length(SF_range) ~= 2
      error('ScansFile %s apparently corrupted', ScansFile);
    end
    if SF_range(2) ~= range(2)
      warning('ScansFile %s range %d-%d differs from input %d-%d', ...
        ScansFile, SF_range, range);
    end
    newval = SF_range(1);
  else
    h = scanview(range(1):range(2));
    waitfor(h);
    result = inputdlg( ...
      { sprintf('Region R%d Starting Scan', Rnum) }, ...
      sprintf('Region R%d', Rnum), ...
      [1 30], ...
      { sprintf('%d', range(1)) });
    newval = str2double(result{1});
  end
  if isnan(newval) || newval < range(1) || newval > range(2)
    error('Invalid Entry: "%s"', result{1});
  end
  new_range = [newval range(2)];
end

function setup_icosfit(region, PTEfile)
  fprintf(1,'Generate icosfit file for %s and %s\n', region, PTEfile);
  PTE = load(PTEfile);
  range = PTE([1,end],1)';
  fitline('update_regions', region, range);
  f = msgbox(sprintf('Invoking fitline for %s using %s',region, PTEfile));
  waitfor(f);
  files = [];
  fitfile = '';
  while isempty(files)
    f = fitline;
    f.Position(1) = 1300-f.Position(3);
    waitfor(f);
    files = dir(sprintf('icosfit.%s.*', region));
    if isempty(files)
      answer = questdlg(sprintf('No icosfit.%s.* found. Continue?',region));
      if ~strcmp(answer,'Yes')
        return;
      end
    else
      if length(files) == 1
        fitfile = files.name;
      else
        fitfile = uigetfile(sprintf('icosfit.%s.*', region));
        if isempty(fitfile)
          files = [];
          answer = questdlg(sprintf('No icosfit.%s.* found. Continue?',region));
          if ~strcmp(answer,'Yes')
            return;
          end
        end
      end
    end
  end
  % Update fitfile with standard tweaks:
  fprintf(1,'Tweak %s\n', fitfile);
  if endsWith(PTEfile, '_nu.txt')
    PTEarg = [ PTEfile ' + nu_F0' ];
  else
    PTEarg = PTEfile;
  end
  icosfit_reconfig(fitfile, '', ...
    'Verbosity', '2', ...
    'MaxEnsembleDriftPerScan', '5e-3 cm-1', ...
    'MaxIterations', '20', ...
    'PTEFile', PTEarg);

  icosfit_slurm(fitfile);
end

function switch_scansdir(newdir)
  fprintf(1,'Switching scansdir to %s\n', newdir);
  Icfg = 'ICOSfit_Config.m';
  if exist(Icfg,'file')
    ifile = Icfg;
  else
    ifile = ['../' Icfg];
  end
  if ~exist(ifile, 'file')
    error('Unable to locate %s', Icfg);
  end
  ofile = [Icfg '.new'];
  fdi = fopen(ifile);
  fdo = fopen(ofile,'w');
  while true
    tline = fgets(fdi);
    if tline == -1; break; end
    if startsWith(tline,'ICOSfit_cfg.ScanDir')
      fprintf(fdo, 'ICOSfit_cfg.ScanDir = ''%s'';\n', newdir);
    else
      fprintf(fdo, '%s', tline);
    end
  end
  fclose(fdi);
  fclose(fdo);
  if exist(Icfg,'file')
    delete(Icfg);
  end
  movefile(ofile, Icfg);
end
