function fig = ghwvdacs(varargin);
% ghwvdacs(...)
% DACS
ffig = ne_group(varargin,'DACS','phwvdacsp','phwvdacst','phwvdacsrh','phwvdacss','phwvdacscpu');
if nargout > 0 fig = ffig; end
