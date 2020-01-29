function [xaprox] = MetNR(f, df, x0, eps)
    k = 1;
    cond = 1;
    x(1) = x0;
    while cond
        k = k + 1;
        x(k) = x(k-1) - f(x(k-1))/ df(x(k-1));
        if abs(x(k) - x(k-1)/ x(k-1)) < eps
            cond = 0;
        end
    end
    xaprox = x(k);
end