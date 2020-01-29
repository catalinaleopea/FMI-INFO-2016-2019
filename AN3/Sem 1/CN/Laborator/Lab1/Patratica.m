%function [y] = Patratica(x)
%    y = x.^2 - 4*x;
%end

%function [z] = Patratica (x, y)
%    z = [x + y; x - y; x ^ 2];
%end

function [z] = Patratica (x)
    z = [x(1) + x(2); x(1) - x(2); x(1) ^ 2];
end