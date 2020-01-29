function [x]=GaussFaraPiv(A,b)
n=size(A,1);
A=[A b];
for k=1:n-1
    indice=0;
    for p=k:n
        if A(p,k)~=0
            indice=p;
        break
        end
    end
    if indice==0
        disp('Sistemul este incompatibil');
    end
    if indice~=k
        L=A(indice,:);
        A(indice,:)=A(k,:);
        A(k,:)=L;
    end
    for l=k+1:n
        m(1,k)=A(l,k)/A(k,k);
        A(l,:)=A(l,:)-m(1,k)*A(k,:);
    end
end
    if A(n,n)==0
        disp('Sist este incomp sau comp nedet')
    end
    x=SubDesc(A(1:n,1:n),A(1:n,n+1));
end
    