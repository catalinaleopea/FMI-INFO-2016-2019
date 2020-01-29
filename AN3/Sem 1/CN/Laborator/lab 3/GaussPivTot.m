function [x]=GaussPivTot(A,b)
n=size(A,1);
A=[A b];
for i=1:n
    index(i)=i;
end
for k=1:n-1
    indicelinie=0;
    indicecol=0;
    max=0;
    for p=k:n
        for m=k:n
            if abs(A(p,k))>max
                max=abs(A(p,k));
                indicelinie=p;
                indicecol=m;
            
            end
        end
    end
    if max==0
        disp('Sistemul este incompatibil sau comp nedet');
    end
    if indicelinie~=k
        L=A(indicelinie,:);
        A(indicelinie,:)=A(k,:);
        A(k,:)=L;
    end
    if indicelinie~=k
        C=A(:,indicecol);
        A(:,indicecol)=A(:,k);
        A(:,k)=C;
        aux=index(indicecol);
        index(indicecol)=index(k);
        index(k)=aux;
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
    