function icosfit_slurm(fitfile)
% icosfit_slurm(fitfile)
% Must be run in the flight analysis directory
% fitfile must match the pattern icosfit.*
flight = getrun(1);
if ~exist(fitfile,'file')
  error('Cannot locate fitfile ''%s''', fitfile);
end
suffix = strrep(fitfile,'icosfit.','');
slurmfile = [flight '.' suffix '.slurm'];
fprintf(1,'Generate slurm file %s for %s\n', slurmfile, fitfile);
fd = fopen(slurmfile,'w');
fprintf(fd,'%s\n','#!/bin/bash');
fprintf(fd,'%s\n','#SBATCH -c 1 # Number of cores requested');
fprintf(fd,'%s\n','#SBATCH -t 300 # Runtime in minutes');
fprintf(fd,'%s\n','#SBATCH -p shared # Partition to submit to');
fprintf(fd,'%s\n','#SBATCH --mem=500 # Memory per node in MB (see also --mem-per-cpu)');
fprintf(fd,'%s\n','#SBATCH --open-mode=append # Append when writing files');
fprintf(fd,'#SBATCH -o %s/logout_%s_%%j.out\n',pwd,suffix);
fprintf(fd,'#SBATCH -e %s/logerr_%s_%%j.err\n',pwd,suffix);
fprintf(fd,'%s\n','#SBATCH --mail-type=END');

fprintf(fd, '%s\n', 'module load foss/2019a');
fprintf(fd, '/n/anderson_lab/Lab/ntallen/icosfit/bin/icosfit %s\n', ...
  fitfile);

fclose(fd);
