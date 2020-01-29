function [L,U,x]=Fact(A,b)
n=size(A,1)
L=zeros(n);
for i=1:n
    L(i,i)=1;
end
t=1;
for k=1:n-1
    indice=0;
    for p=k:n
        if A(p,k)~=0
            indice=p;
            termenliber(t)=indice;
            t=t+1;
            break
        end
    end
    if indice==0
        disp('Sist inc sau comp nedet');
    end
    if indice~=k
        Linie=A(indice,:)
        A(indice,:)=A(k,:);
        A(k,:)=Linie;
    end
    for l=k+1:n
        m(l,k)=A(l,k)/A(k,k);
        L(l,k)=m(l,k);
        A(l,:)=A(l,:)-m(l,k)*A(k,:);
    end
end
if A(n,n)==0
    disp('Sistem incompatibil sau compatibil');
end
L
U=A
for t=1:size(termenliber)
    if termenliber(t)~=t
        aux=b(t);
        b(t)=b(termenliber(t));
        b(termenliber(t))=aux;
    end
end
y=SubAsc(L,b);
x=SubDesc(U,y);
x
end
