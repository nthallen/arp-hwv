function vars = load_seac4rs_merge(ICARTT_Filename)
%vars = load_seac4rs_merge(ICARTT_Filename)
%  Imports data from the specified file
%  ICARTT_Filename:  file to read
%  vars: struct containing data
fid = fopen(ICARTT_Filename,'r');
if fid < 0
    error('Cannot open input file "%s"', ICARTT_Filename);
end
tline = fgets(fid);
fclose(fid);
comma = find(tline == ',',1);
if isempty(comma)
    error('Invalid ICARTT format');
end

DELIMITER = ',';
HEADERLINES = str2double(tline(1:comma-1));
ID = importdata(ICARTT_Filename, DELIMITER, HEADERLINES);

for i = 1:size(ID.colheaders, 2)
    var = ID.colheaders{i};
    S = find(var ~= ' ',1);
    var(var == '-') = '_';
    vars.(var(S:end)) = ID.data(:,i);
end

