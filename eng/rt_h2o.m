function rt_h2o
URL1 = 'http://asp-interface-2.arc.nasa.gov/API/parameter_data/N809NA/HWV';
URL2 = 'http://asp-interface-2.arc.nasa.gov/API/parameter_data/N809NA/IWG1';
URL3 = 'http://asp-interface-2.arc.nasa.gov/API/parameter_data/N809NA/CJLH';
AppData.Data1 = rt_data(URL1, 'HWV', 'T', 'status', 'h2ov');
AppData.Data2 = rt_data(URL2, 'IWG1', 'T', 'Lat', 'Lon', 'Alt', ...
    '', '', '', '', '', '', '', '', '', '', '', '', '', '', ...
    '', '', '', '', '', '', '', '', '', '', '', '', '', '');
AppData.Data3 = rt_data(URL3, 'CJLH', 'T', 'h2ov');
Axes = [
    60    45    60     1    20    15     0     .5   0
    60    45    60     1     0    45    60     1    0
    ];

rt_viewer('Name','HWV Viewer', 'Callback', @rt_h2o_callback, ...
    'Axes', Axes, 'AppData', AppData);

function draw = rt_h2o_callback(handles, cmd, Axes)
% handles: the usual
% cmd: 'Acquire' (with Axes), 'Draw' (with Axes), 'ExportData'
AppData = handles.data.AppData;
draw = 0;
if strcmp(cmd, 'Acquire')
    pause(5);
    handles = guidata(handles.scan_viewer);
    if handles.data.CloseRequested
        return;
    end
    handles.data.AppData.Data1 = rt_data(AppData.Data1);
    handles.data.AppData.Data2 = rt_data(AppData.Data2);
    handles.data.AppData.Data3 = rt_data(AppData.Data3);
    guidata(handles.scan_viewer, handles);
    if handles.data.AppData.Data1.fresh || ...
            handles.data.AppData.Data2.fresh || ...
            handles.data.AppData.Data3.fresh
        draw = 1;
    end
elseif strcmp(cmd, 'Draw')
    rt_h2o_draw(handles, Axes);
    handles.data.AppData.Data1.fresh = 0;
    handles.data.AppData.Data2.fresh = 0;
    handles.data.AppData.Data3.fresh = 0;
elseif strcmp(cmd, 'ExportData')
    rt_data(handles.data.AppData.Data1);
    rt_data(handles.data.AppData.Data2);
    rt_data(handles.data.AppData.Data3);
end

function rt_h2o_draw(handles, Axes)
D1 = handles.data.AppData.Data1;
D3 = handles.data.AppData.Data3;
plot(Axes(1), time2d(D1.value.T(1:D1.N)), D1.value.h2ov(1:D1.N), '.-', ...
    time2d(D3.value.T(1:D3.N)), D3.value.h2ov(1:D3.N),'.-');
ylabel(Axes(1),'h2ov ppm');
set(Axes(1),'YAxisLocation','Right','xticklabel',[]);
if D1.N
    if D3.N
        legend(Axes(1),'HWV','JLH','Location','Northwest');
    else
        legend(Axes(1),'HWV');
    end
elseif D3.N
    legend(Axes(1),'JLH');
end
xlo = handles.data.xlim{1};
if ~isempty(xlo)
    xl = xlim(Axes(1));
    if (xl(2) > xlo(2))
        xl = xlo + xl(2) - xlo(2);
        handles.data.xlim{1} = xlo;
    end
end
D2 = handles.data.AppData.Data2;
plot(Axes(2), time2d(D2.value.T(1:D2.N)), D2.value.Alt(1:D2.N)/1000, '.-');
xlo = handles.data.xlim{2};
if ~isempty(xlo)
    xl = xlim(Axes(2));
    if (xl(2) > xlo(2))
        xl = xlo + xl(2) - xlo(2);
        handles.data.xlim{2} = xlo;
    end
end
ylabel(Axes(2),'Alt km');
xlabel(Axes(2),'Seconds Since Midnight UTC');
linkaxes(Axes,'x');
guidata(handles.scan_viewer, handles);

function data = rt_data(varargin)
% data = rt_data(url, 'HWV', 'T', 'status', 'h2ov'); % initialize data structure
%   Initialize data collection
% data = rt_data(data);
%    Append data to the end.
% rt_data(data, 'Export');
%    Export data to Matlab
if ischar(varargin{1})
    data.N = 0;
    data.lastT = 0;
    data.Nmax = 0;
    assert(nargin >= 4);
    data.url = varargin{1};
    data.hdr = varargin{2};
    data.fmt = [ data.hdr ',%f-%f-%fT%f:%f:' ];
    data.fld = { varargin{3:end} };
    data.Nfld = length(data.fld);
    data.epoch = datenum(1970,1,1,0,0,0);
    data.src = sprintf('%s.1.raw', data.hdr);
    data.tmp = sprintf('%s.1M.raw', data.hdr);
    data.fresh = 0;
    for i = 1:data.Nfld
        data.fmt = [ data.fmt '%f' ];
        if ~isempty(data.fld{i})
            data.value.(data.fld{i}) = [];
        end
    end
    % find bash
    cwp = '';
    for cp = { 'C:\cygwin', 'C:\cygwin.hide' }
        cwpt = [cp{1} '\bin\bash.exe'];
        if exist(cwpt,'file')
            cwp = cwpt;
            break;
        end
    end
    % find collect
    collect = win2cyg(which('rt_collect.sh'));
    cmd = sprintf('start %s ''%s'' %s %s', ...
        cwp, collect, data.hdr, data.url);
    % fprintf(1,'Command is %s\n', cmd);
    [s,w] = unix(cmd);
    if s ~= 0
        error('Failed to start rt_collect: "%s"', w);
    end
else
    data = varargin{1};
    if nargout == 0
        flds = fieldnames(data.value);
        for i = 1:length(flds)
            vals.(flds{i}) = data.value.(flds{i})(1:data.N);
        end
        assignin('base', data.hdr, vals);
        return;
    end
end
try
%     if data.N == 0
%         raw = urlread([ data.url '?Start=0']);
%     else
%         raw = urlread(data.url);
%     end
%     C = textscan(raw, data.fmt, 'Delimiter', ',');
    if exist(data.src,'file') && movefile(data.src, data.tmp)
        fid = fopen(data.tmp, 'r');
        C = textscan(fid, data.fmt, 'Delimiter', ',');
        fclose(fid);
        delete(data.tmp);
        req_size = data.N + length(C{1});
        if req_size > data.Nmax
            newsize = ceil(max([data.Nmax*1.5  128  req_size*1.5]));
            iN = 1:data.N;
            z = zeros(newsize,1);
            for i = 1:data.Nfld
                mnc = data.fld{i};
                if ~isempty(mnc)
                    newval = z;
                    newval(iN) = data.value.(mnc)(iN);
                    data.value.(mnc) = newval;
                end
            end
            data.Nmax = newsize;
        end
        T = (datenum(C{1},C{2},C{3},C{4},C{5},C{6}) - data.epoch) * 86400;
        iN = data.N+1:req_size;
        data.value.(data.fld{1})(iN) = T;
        for i = 2:data.Nfld
            mnc = data.fld{i};
            if ~isempty(mnc)
                data.value.(mnc)(iN) = C{i+5};
            end
        end
        data.N = req_size;
        data.fresh = 1;
    end
catch
    t=clock;
    fprintf(1, sprintf('Something failed for %s at %02d:%02d:%02.0f\n', ...
        data.hdr,t(4),t(5),t(6)));
end

% function data = rt_parse(text, header)
% nhdr = length(header)+2;
% timetext = text(nhdr:nhdr+25);
% T = time2d(convert_iso8601(timetext));
% rest = [ text(nhdr+26:end) ','];
% commas = find(rest == ',');
% data = NaN * zeros(1,length(commas));
% data(1) = T;
% for i=1:length(commas)-1
%     data(i+1) = str2double(rest(commas(i)+1:commas(i+1)-1));
% end