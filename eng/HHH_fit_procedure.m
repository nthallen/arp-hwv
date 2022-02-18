%%
PTEref = '../PTEref.txt';
PTEref_row = 15;
PTE = load(PTEref);
PTE_params = PTE(PTEref_row,4:end);
clear PTE;
%%
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
r = r([1 3]);
[~,I] = sort(r);
for region = 1:length(I)
  wvno = ranges(I(region)).wvno;
  wvname = wvs(wvno).Name;
  range = ranges(I(region)).ranges;
  fprintf(1,'Region %d: %s %d-%d\n', region, wvname, range);
  if strcmp(wvname,'HHH_10Hz')
    Rnum = region + 10;
  else
    Rnum = region;
  end
  range = get_starting_scan(Rnum, range);
  PTEfile = sprintf('PTE_gen_R%d.txt',Rnum);
  if exist(PTEfile,'file')
    fprintf(1,'Skipping PTE_gen %s over %d-%d\n', PTEfile, range);
  else
    fprintf(1,'Generate %s over %d-%d\n', PTEfile, range);
    scans = range(1):range(2);
    PTE_gen(scans, PTEfile,PTE_params);
  end
  if strcmp(wvname,'HHH_10Hz')
    Rnum = region;
    Rtxt = sprintf('R%d',Rnum);
    oPTEfile = sprintf('PTE_gen_%s.txt', Rtxt);
    if exist(oPTEfile,'file')
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
waves_used
% Then set scans and run scanview(scans) to decide where to start
%%
edit_ICOSfit_cfg; % to switch to the averaged scans
%%
% define R1A that covers all the average data
PTE = load('PTE_gen_10Hz.average1.txt');
fitline('update_regions','R1A',PTE([1 end],1));
clear PTE
%%
fitline % to initialize icosfit file
%%
% Update the fitfile name
suffixes = 'R1.1Hz5p3er';
fitfile = [ 'icosfit.' suffixes ];
base = ['ICOSout.' suffixes ];
%%
% Update fitfile with standard tweaks:
icosfit_reconfig(fitfile, '', ...
  'Verbosity', '2', ...
  'MaxEnsembleDriftPerScan', '5e-3 cm-1', ...
  'MaxIterations', '20');
%%
% Now run icosfit outside Matlab
%%
% Take a first look to see how things went
mixlines(base);
S = ICOS_setup(base);
figure; plot(S.scannum, S.nu_F0);
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
  h = scanview(range(1):range(2));
  waitfor(h);
  result = inputdlg( ...
    { sprintf('Region R%d Starting Scan', Rnum) }, ...
    sprintf('Region R%d', Rnum), ...
    [1 30], ...
    { sprintf('%d', range(1)) });
  newval = str2double(result{1});
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
  icosfit_reconfig(fitfile, '', ...
    'Verbosity', '2', ...
    'MaxEnsembleDriftPerScan', '5e-3 cm-1', ...
    'MaxIterations', '20');

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
