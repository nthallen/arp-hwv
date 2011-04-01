function fig = ghwvf(varargin);
% ghwvf(...)
% Flow
ffig = ne_group(varargin,'Flow','phwvft','phwvfpib','phwvfpif','phwvfsfb');
if nargout > 0 fig = ffig; end
