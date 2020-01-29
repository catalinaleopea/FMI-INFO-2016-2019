function [x]=SubAsc(A,b)
x(1)=1/A(1,1)*b(1);
for k=2:size(A,1)
    suma=sum(A(k,1:k-1).*x(1:k-1));
    x(k)=1/A(k,k)*(b(k)-suma);
end
end