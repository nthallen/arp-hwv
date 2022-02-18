%%
PTEref = '../PTEref.txt';
PTEref_row = 15;
PTE = load(PTEref);
PTE_params = PTE(PTEref_row,4:end);
clear PTE;
%%
waves_used
% Then set scans and run scanview(scans) to decide where to start
%%
% For 1Hz
scans = 5:11903;
PTEfile = 'PTE_gen.txt';
PTE_gen(scans,PTEfile,PTE_params);
%%
PTE = load(PTEfile);
fitline('update_regions','R1',PTE([1 end],1));
clear PTE
%%
% For 10Hz
scans = 5:11903;
PTEfile = 'PTE_gen_10Hz.txt';
PTE_gen(scans,PTEfile,PTE_params);
fprintf(1,'Now average\n');
average_spectra2(1,PTEfile);
PTEfile = 'PTE_gen_10Hz.average1.txt';
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