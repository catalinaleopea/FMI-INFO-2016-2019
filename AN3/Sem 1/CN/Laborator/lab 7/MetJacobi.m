function [xAprox, N] = MetJacobi(A, a, epsilon)
    %q = norm(eye(length(A)) - A, Inf);
    %sau
    q = max(max(eye(A) - A));
    if(q >= 1)
        disp('Met Jacobi nu asigura convergenta');
        return;
    end
    xNum = zeroes(n, 1);
    k = 1;
    B = eye(n) - A;
    ok = 1;
    while (ok)
        k = k + 1;
        xNum = B*xNum + a;
        