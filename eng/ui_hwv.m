function ui_hwv
f = ne_dialg('Harvard Water Vapor',1);
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'newtab', 'Lyman Alpha');
f = ne_dialg(f, 'add', 0, 1, 'ghwvlaho', 'H2O' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlahoppm', 'PPM' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlala', 'Lamp A' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalat', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalap', 'Pres' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalarf', 'RF' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalairv', 'IRV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalac', 'Current' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalas', 'Status' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlaairv', 'A IRV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlaairvirv', 'IRV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlaairvdirvdt', 'dIR Vdt' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlalb', 'Lamp B' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalbt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalbp', 'Pres' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalbrf', 'RF' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalbirv', 'IRV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalbs', 'Status' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwvlalc', 'Lamp C' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalcp', 'Pres' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalcrf', 'RF' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalcirv', 'IRV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalct', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlalcs', 'Status' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlasdp', 'SDP' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlasdpdp', 'DP' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlasdpt', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlasdpp', 'P' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlaf', 'Flow' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlafsfb', 'SFB' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlacs', 'Ct Stat' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlacsc', 'Ct 0' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlacsct1', 'Ct 1' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlacsct2', 'Ct 2' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwvlac', 'Counts' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlaca', 'A' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlacb', 'B' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlacc', 'C' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvlass', 'Sol St' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlassa', 'A' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlassb', 'B' );
f = ne_dialg(f, 'add', 1, 0, 'phwvlassc', 'C' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'newtab', 'HK');
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkgd', 'Gas Deck' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkgdt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkgdp', 'Pres' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkc', 'Current' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkcl', 'Lamps' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkclab', 'Lab' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkcmz', 'MZ' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkca', 'Air' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkcs', 'Spare' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhk_commands', 'Commands' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhk_commandsds', 'DS' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhk_commandss', 'S' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkp', 'Power' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkps', 'Switches' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkpt', 'Temp' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkf', 'Flow' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkft', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkfpib', 'PIB' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkfpif', 'PIF' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkl', 'Lab' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhklsp', 'Set Pt' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhklf', 'Flow' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhklp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhklt', 'T' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkmz', 'MZ' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkmzt', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkmzct', 'CT' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkmzs', 'Set' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkg', 'General' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkgsws', 'SW Stat' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkgioss', 'IO Sw S' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkgais', 'AI Stat' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkt', 'Throttle' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhktp', 'Pot' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhktb', 'Bits' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkts', 'Step' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkdacs', 'DACS' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacsp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacst', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacsrh', 'RH' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacss', 'Status' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacscpu', 'CPU' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkdacsm', 'Memory' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhkhkp', 'HK Power' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkhkpv', 'Voltage' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkhkpc', 'Current' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhkhkps', 'Status' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'newtab', 'HHH');
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhf', 'Flow' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhfp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhft', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhfdp', 'DP' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhhpv', 'HPV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhpvt', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhpvp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhpvrh', 'RH' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhpvlte', 'LTE' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhpvi', 'I' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhspv', 'SPV' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhspvt', 'T' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhspvp', 'P' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhspvrh', 'RH' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhspvs', 'Status' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhqcli', 'QCLI' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhqclis', 'Stale' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhqcliw', 'Wave' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhqcliqcli', 'QCLI s' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhssp', 'SSP' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspovf', 'OVF' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspn', 'Num' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspsn', 'SN' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhssps', 'Stale' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspstatus', 'Status' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspts', 'T Skip' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhsspt', 'T' );
f = ne_dialg(f, 'add', 0, 1, 'ghwvhhhhk', 'HK' );
f = ne_dialg(f, 'add', 1, 0, 'phwvhhhhkt', 'T' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'newtab', 'IWG1');
f = ne_dialg(f, 'add', 0, 1, 'ghwviwgiwg', 'IWG1' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwgl', 'Lat' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwglon', 'Lon' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwgt', 'Temp' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwgp', 'Pres' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwgs', 'Speed' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwgm', 'Mach' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgiwga', 'Alt' );
f = ne_dialg(f, 'add', 0, 1, 'ghwviwga', 'Attitude' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgaa', 'Attack' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgap', 'Pitch' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgar', 'Roll' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgass', 'Side Slip' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgad', 'Drift' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgasz', 'SZ' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgaaz', 'AZ' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwga_az', 'Az' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgat', 'Track' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'add', 0, 1, 'ghwviwgw', 'Wind' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgwvv', 'Vert Vel' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgwvs', 'Vert Speed' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgwd', 'Dir' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwgws', 'Speed' );
f = ne_dialg(f, 'add', 0, 1, 'ghwviwg1_iwg1_stat', 'IWG1 Stat' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwg1_iwg1_statcp', 'Cabin Press' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwg1_iwg1_stattd', 'T Drift' );
f = ne_dialg(f, 'add', 1, 0, 'phwviwg1_iwg1_stats', 'Stale' );
f = ne_dialg(f, 'newcol');
f = ne_dialg(f, 'newtab', 'Runs');
f = ne_listdirs(f, 'HWV_Data_Dir', 13);
f = ne_dialg(f, 'newcol');
ne_dialg(f, 'resize');
