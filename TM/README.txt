This file includes general notes that experimenters and developers might need
to refer to to refamiliarize themselves with how the instrument operates and
the code is organized.

Mixing Ratio Calculations
  Lyman Alpha
    The code for Lyman Alpha H2O mixing ratio calculation starts with
    H2Omr2.tmc and references suppport functions in the LyAmr subdirectory.
    H2Omr2.tmc includes a number of calibration constant definitions that
    may need to be adjusted. There are options within this file for
    selecting different source variables for pressure and temperature
    by way of software status commands prefixed with 'SW Status LyA Use'.
    Needless to say, the calibration constants relative to the different
    input variables should be periodically reviewed and/or calibrated.
    
    The lyamrext extraction produces lyamreng.csv, which reports the
    mixing ratio along with P, T and M that were used in the calculation
    for comparison to independently derived values.
    
  HHH
    HHH used icosfit, driven by icosfitd, to calculate mixing ratio.
    The code for that is mostly contained under the driver directory
    in /home/hwv/src/icosfitd/TM. icosfit.RT.in.in defines all the
    important icosfit parameters to be used in the fit.
    
    src/TM/icosfitd.tma contains the code to define the P and T for
    the fit, and should be reviewed and modified whenever these are
    calibrated.
    
    The actual P and T used is written to PTE.log and also reported in
    ICOSsum.log along with the fit results.
  
Realtime Transmission
  UDP.tmc is where the status packet definition is found.
    

Data Handling Procedures
  In order to optimize extraction of data from the flight computer,
  we will try copying directly to an external hard drive in order to
  avoid the slow network transfer. This is complicated by the need to
  copy between incompatible file systems. After considering various
  options and running benchmark tests, we have concluded that the
  best current strategy is to copy to a Linux ext3 partition on a
  removable disk drive. This format can be read on Linux and Windows
  computers. For Windows machines, a driver must be installed first
  (Ext2Fsd).
  
  We hope that transferring to the removable drives will be relatively
  convenient. It also supports our need to archive flight data to
  multiple locations. We are guessing that from this point forward,
  we will want to archive all runs of types cal, preflt and flight.
  We may or may not want to review the data from runs of type junk
  or data, but we will probably not archive it on the removable drives.
  
  Post Run Procedure:
    Run 'reduce' to create the run and copy the engineering data to
      the GSE. SSP scans will not be copied (by default) for run types
      cal, preflt and flight. SSP scans *will* be copied by default
      for run types junk and data. dircksum will be run automatically
      for runs of type flight. If you don't want to copy anything,
      use 'saverun' instead.
    As soon as reduce is completed (or even while dircksum is running),
      the engineering data is ready to be reviewed using 'getrun'
    Reboot with external drive connected
    On the GSE, run 'transfer -wdc' to copy all runs of type cal,
      preflt or flight from the flight computer onto the removable.
      You will be prompted to confirm what runs will be copied and
      have an opportunity to select specific runs if necessary.
    On the GSE, run 'transfer shutdown', then swap external drives,
      reboot, and do it again.
    Take removable drive to your data analysis system and start
      analyzing.
  
Debian on external drive
    On GSE, create /home/flight/.ssh/id_rsa*
    visudo to add
      (flight) /usr/local/bin/transfer
    to list of apps FLIGHT users can run.
    Copy transfer into /usr/local/bin
    Setup alias IP address 10.16.16.1/24
      /sbin/ifconfig en0 inet 10.16.16.1 netmask 255.255.255.0 alias
    [move transfer and remtransfer into tmutil]
    
  First Drive
    15 GB Boot partition ext3
    2 GB Swap partition
    Rest is /data ext3
    If install fails, regenerate the USB install stick
    Create account for me (nort) with QNX password
    Create account for flight with rooty password
      Copy relevant ssh keys into my account (cygwin, nortvm650a, *gse)
      Copy relevant ssh keys into flight account (*gse)
    Install sshd, rsync
    edit /etc/fstab to mount /qnx4
       /dev/sda2 /qnx4 qnx4 ro,nofail 0 0
       # I don't know why there is a FAT partition in there...
    edit /etc/network/interfaces
    visudo to add
      Defaults editor=/usr/bin/vi
      %flight ALL=(root) NOPASSWD /sbin/shutdown
    Copy remtransfer into /usr/local/bin and edit for instrument
    Copy dircksum and dircompare into /usr/local/bin
    delete /etc/udev/rules.d/*-persistent-net.rules before switch to flight system
    
    Copy configuration files to blast onto subsequent dists
    
  Subsequent Drives
    15 GB Boot partition ext3
    2 GB Swap partition
    Rest is /data ext3
    If install fails, regenerate the USB install stick
    Create account for me (nort) with QNX password
    Install sshd (should have been selected earlier), sudo
      apt-get install sudo
    edit /etc/fstab to mount /qnx4
       /dev/sda2 /qnx4 qnx4 ro,nofail 0 0
       # I don't know why there is a FAT partition in there...
    Copy configuration tar.gz and install
    delete /etc/udev/rules.d/*-persistent-net.rules before switch to flight system
    
    Fixed IP 10.16.16.2 (so not dependent on lab network)
    ssh in to perform copy operation.
