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
clnnames = clean_vars(ID.colheaders);
for i = 1:length(clnnames)
    vars.(clnnames{i}) = ID.data(:,i);
end

function cln = clean_vars(vars)
cln = cell(length(vars),1);
for i = 1:length(vars)
    var = var_cleanup(vars{i});
    cln{i} = var;
    % vars.(var) = ID.data(:,i);
end
[unames,~,J] = unique(cln);
if length(unames) ~= length(cln)
    [JS,JI] = sort(J);
    dJS = [0; diff(JS)==0];
    dups = find(diff(dJS)>0);
    %dups = find(diff(JS) == 0);
    for dup=dups'
        l = find(JS == JS(dup));
        fprintf(1,'Warning: ');
        fprintf(1,'''%s'', ', vars{JI(l)});
        fprintf(1,'all map to ''%s''\n', unames{J(JI(l(1)))});
    end
end

function clean_var = var_cleanup(var)
var(var == '-') = '_';
v = isletter(var) | isdigit(var) | (var == '_');
clean_var = var(v);
