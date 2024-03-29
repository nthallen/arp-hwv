Engineering Graphs in Matlab
	Setup
		There are three Matlab libraries you will need to install to run the
		engineering plot gui:
			nort: A set of general utility functions
			nort/ne: Functions for engineering plots
			HWVeng: HWV-specific engineeering plots
		Installation involves checking out the libraries from CVS and adding
		them to your Matlab path.
		
		Decide where you want the Matlab libraries to go.
			You probably want to create a base directory for your Matlab
			libraries. This could be a Matlab directory in "My Documents" or
			C:\Matlab. All three of these libraries could then be subdirectories
			of this root directory. On the other hand, you might have all of
			the HWV source code checked out somewhere, so it might make sense
			to leave the HWV-specific engineering plot library where it is.
		
		Download Nort's matlab libraries:
			cvs -d :ext:forge.abcd.harvard.edu:/cvsroot/arp-das co -d nort Matlab/nort
				or
			cvs -d :pserver:anonymous@forge.abcd.harvard.edu:/cvsroot/arp-das login
			cvs -d :pserver:anonymous@forge.abcd.harvard.edu:/cvsroot/arp-das co -d nort Matlab/nort
			
			There are several directories included in this download, but only two that
			should be added to your Matlab path: nort and nort/ne. The others contain
			examples of installation-specific configuration hooks to make other parts
			of the libraries work.

		Download HWV engineering plot directory
			cvs -d :ext:forge.abcd.harvard.edu:/cvsroot/arp-w-cims co -d HWVeng HWV/eng
				Note that this is part of the HWV source hierarchy, so if you already have
				that checked out, cvs update -d should bring it in.
		
		Add nort, nort/ne and HWVeng directories to your Matlab path

		Decide on a root directory for flight/run data
			This directory will contain a subdirectory for each run using the same
			run numbering as under QNX. If you append an 'F' to the name of flight
			runs, then the plots will note that this is flight data.
			
			Each run directory will contain .mat files with all the engineering
			data.
		
		Create HWV_Data_Dir.m (probably in your HWVeng directory):
			function path = HWV_Data_Dir
			% path = HWV_Data_Dir;
			path = 'C:\Data\HWV';

	Setup for a specific run:
		Extract engineering data on QNX:
			extract raw/flight/120504.2 HWVengext
		Copy extract .csv files into HWV_Data_Dir
			I have a script called 'getrun' that I place in the HWV_Data_Dir.
      See below for details on installing and running getrun.
		
		Convert the .csv files to .mat files:
			In Matlab, cd to the run directory and run csv2mat. You can delete the .csv files
			after the .mat files are created. Note that when properly configured, getrun will
      handle this step for you.
			
		Now you have completed the setup for this run. Hereafter, this run's data will be
		readily accessible to the GUI.
		
	Run the GUI:
		ui_hwv
			Select the run from the list on the right. The most recent run is the default.
			Each button in the main area generates a graph. The larger buttons represent
			groups that put multiple graphs on one figure. The grouping is easily
			configurable, so if there are different combinations you'd like to see, let
			me know.
			
			I have added some menu items to the graph displays.
				Zoom: Added before Matlab added their zoom buttons, but still sometimes
					a little easier to use.
				MatchX: After zooming in on an X-axis region in one graph, MatchX will
					zoom all the other graphs in the figure to the same X range.
				Edit: Allows you to further customize the graphs.
				Expand: Allows you to open any of the graphs in it's own figure.
			
	Customization:
		The selection of which data gets displayed in which group is determined
		by the file genui.txt in the telemetry source directory. The program
		that generates the .m files is called 'genui', and it also creates
		the extraction required. The format of genui.txt is documented in
		the usage message for genui, so 'use genui' will explain it.
		
		You will often want to further customize individual graphs. The use of
		lines may be inappropriate on particularly noisy data, for example, or
		the default limits may reflect a transient startup condition, not the
		region of interest. You can edit the .m file for any graph. Most consist
		of a single invocation of my timeplot() function returning vector of
		graphic object handles. You can add statements that alter the graphic
		objects. This is an example from the Harvard Water Vapor instrument:
		
			function phwvsdpp(varargin);
			% phwvsdpp( [...] );
			% SDP P
			h = timeplot({'SD_HP','SD_LP','UVB1_Counts*0.08'}, ...
						'SDP P', ...
						'P', ...
						{'SD\_HP','SD\_LP','UVB1\_Counts'}, ...
						varargin{:} );
			set(h,'LineStyle','none','Marker','.');
			ax = get(h(1),'parent');
			set(ax,'ylim',[0 800]);

		This switches the graphs from lines to symbols and fixes the Y-axis
		limits at [0 800].
		
		Such modifications can be checked back in to CVS to make them available
		to other team members. Subsequent changes to genui.txt will overwrite
		the modifications, but if they are checked in, it is possible to
		reconstruct them. [Ideally I would come up with a system whereby
		modifications would persist...]

==========================================
Instructions for setting up getrun for HWV
==========================================

First of all, make sure to run cvs update in:

  - Matlab/nort
  - HWVeng

Your local directory names may be somewhat different, but I think 
you should be able to figure out what I'm talking about. 

One caveat: If you used the anonymous CVS instructions, cvs will 
not work from the hangar unless you use the VPN. From the hotel, 
it should be fine.

Now there is a shell script in the HWVeng directory called 'getrun'.
Copy this into C:/Data/HWV or whatever folder you use for data.
You should also copy the Matlab script HWV_startup.m into that
directory and rename it startup.m.

You will probably want to edit getrun to customize where it will
put the files it downloads. I have it set up to create run
directories undir SEAC4RS/RAW, and then I create analysis
directories under SEAC4RS. (This was motivated mostly by Carbon,
where we needed three separate analysis directories for each
flight, so I created separate analysis dirs under CO2, MINI
and ISO) You can change this organization by changing the
following definitions near the top of getrun:

  HHH_Dir=SEAC4RS
  RAW_Dir=SEAC4RS/RAW

For example, if you want to just dump everything in C:/Data/HWV,
you could define these as:

  HHH_Dir=.
  RAW_Dir=.

There is also a definition for the hostname of the GSE:

  gse=hwvgse.arp.harvard.edu

This will work if you have a customized ~/.ssh/config file
that will map that name to an IP address. Mine includes:

  host hwvgse.arp.harvard.edu
  hostname 10.16.16.3

Another reason for using this file is if your windows username
is different from your QNX username. You can add a 'user' line
if necessary so ssh will use the correct one. You can test your
ssh configuration by issuing the command:

  ssh hwvgse.arp.harvard.edu
  
If you get an error about not being able to resolve the name or
not being able to reach the host, you probably need to configure
~/.ssh/config (or connect the ethernet!) If you get a prompt
for your QNX password, you'll want to setup an ssh key.
getrun will work without doing this, but it will prompt you
several times for each run.

  cd ~
  pwd
  # if pwd does not show something reasonable like /home/mracine,
  # let me know. We may need to clean up a few things
  mkdir .ssh # which may complain if the directory already exists
  ssh-keygen -t rsa
  # When prompted for passphrase, just hit enter and again when
  # asked to confirm
  # When prompted for the filename, the default should be something
  # like ~/.ssh/id_rsa. If so, accept it.
  # This actually creates two files: id_rsa and id_rsa.pub
  scp id_rsa.pub hwvgse.arp.harvard.edu:.

Now go to the GSE, log in (or make sure it's you who is logged in):

  cd
  mkdir .ssh # which may complain if the directory already exists
  cat id_rsa.pub >>.ssh/authorized_keys

Now back on your windows machine:

  ssh hwvgse.arp.harvard.edu

Ideally this will log you in without a password prompt. If you are
still getting a prompt for a password, you'll need to double check
the permissions on your home directory and the .ssh directory. Neither
can allow group write permissions.

===============
Running getrun:
===============

The basic command is:

  ./getrun <runtype> <run>
  
where of course you have replaced <runtype> with flight, preflt, cal,
data or junk, and you have replaced <run> with the run number. You
can omit the <runtype>, but if you include it, getrun will copy HWV.log
and saverun.log in addition to the .csv files. If you are dealing with
a data run that isn't archived onto the removable drives, you can add
the keyword 'HHH' before the <run> argument to ask getrun to also copy
the SSP directory. (You must include the <runtype> arg if you include
HHH)

Also, you can list more than one run on the ./getrun command line,
so it's possible to download the data for all the flights in one
shot.

