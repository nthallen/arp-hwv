#! /bin/bash
# Install script for ICOSfit, HHH
function nl_error {
  echo "icosfit_matlab_setup: $*" >&2
  exit 1
}

ICOSFIT_MATLAB_DIR=/usr/share/icosfit/Matlab

scriptname=hwv_icosfit_matlab_setup
ofile=$scriptname.m
OS=`uname -s`
use_cygpath=no
case "$OS" in
  CYGWIN_NT*) machine=Cygwin;;
  Linux) machine=Linux;;
  Darwin) machine=Mac;;
  *) nl_error "Unable to identify operating system: uname -s said '$OS'";;
esac

for dir in '' /ICOSfit /arp-das; do
  [ -d $ICOSFIT_MATLAB_DIR$dir ] ||
    nl_error "Directory missing from installation: $ICOSFIT_MATLAB_DIR$dir"
done

touch $ofile
if [ ! -f $ofile ]; then
  echo "ERROR: Unable to create Matlab setup script in the current directory."
  echo "You should cd to a writable directory and then rerun this script"
  fp=$0
  case "$fp" in
    /*) :;;
    ./*) fp=$PWD/${0#./};;
    *) fp=$PWD/$0;;
  esac
  echo "using the full path: $fp"
fi

# wrap_path path
# wrap_path path varname
# Assigns wrapped path to global variable path_wrapped
# If varname is provided, also copies the wrapped path to the specified variable
function wrap_path {
  path=$1
  varname=$2
  case "$machine" in
    Cygwin) path_wrapped="`cygpath -w $path`";;
    *) path_wrapped=$path;;
  esac
  [ -n "$varname" ] && eval $varname='$path_wrapped'
}

method='https://'
[ "$1" = "ssh" ] && method='ssh://git@'
[ -d SW ] || mkdir SW
[ -d Data ] || mkdir Data
[ -d Data/HWV ] || mkdir Data/HWV
[ -d Dtaa/HWV/HHH ] || mkdir Data/HWV/HHH
cd SW
git clone ${method}github.com/nthallen/arp-das-matlab.git
wrap_path $PWD/arp-das-matlab arp_das_matlab_wrap_path
wrap_path $PWD/arp-das-matlab/ne arp_das_matlab_ne_wrap_path
git clone ${method}github.com/nthallen/arp-hwv.git
wrap_path $PWD/arp-hwv/eng arp_hwv_eng_wrap_path
cat >$ofile <<EOF
fprintf(1,'Running $scriptname to setup Matlab PATH for HWV\n');
addpath('$arp_das_matlab_wrap_path');
addpath('$arp_das_matlab_ne_wrap_path');
addpath('$arp_hwv_eng_wrap_path');
savepath;
delete $ofile
fprintf(1,'HWV Setup complete\n');
pause(2);
quit
EOF

cd ..
cp SW/arp-hwv/eng/getrun Data/HWV/
wrap_path $PWD/Data/HWV/HHH/RAW RAW_wrap_path

cat >Data/HWV/HHH/ICOSfit_Config.m <<EOF
function ICOSfit_cfg = ICOSfit_Config;
ICOSfit_cfg.Matlab_Path = '$RAW_wrap_path';
ICOSfit_cfg.ICOSfit_Path = '$PWD/Data/HWV/HHH/RAW';
ICOSfit_cfg.WavesFile = 'waves.m';
ICOSfit_cfg.ScanDir = 'SSP';
EOF

srcdir=/usr/share/icosfit/setup/hwv
for file in Cell_Config.m fitline.dat sbase.3p.ptb sbase.5p.ptb; do
  cp $srcdir/$file Data/HWV/HHH/
done
  

# Now locate matlab and run it, specifying this directory and the
# name of the newly created set script
S=`which matlab 2>/dev/null`
if [ -n "$S" ]; then
  matlab=matlab
else
  for path in /Applications/MATLAB*; do
    [ -e $path/bin/matlab ] && matlab=$path/bin/matlab
  done
fi

wrap_path $PWD/SW SW_wrap_path
if [ -n "$matlab" ]; then
  echo "Starting $matlab to complete setup"
  eval $matlab -sd '$SW_wrap_path' -r $scriptname
else
  nl_error "Unable to locate Matlab executable"
fi
