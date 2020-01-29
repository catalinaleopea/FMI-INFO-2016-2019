function [x]=SubDesc(A,b)
n=size(A, 1);
x(n)=1/A(n,n)*b(n);
k=n-1;
while k>0
    suma=0;
    for j=k+1:n
        suma=suma+A(k,j)*x(j);
    end
    x(k)=1/A(k,k)*(b(k)-suma);
    k=k-1;
end
end