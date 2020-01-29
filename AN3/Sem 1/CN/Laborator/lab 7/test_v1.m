%% comentariu
% A = zeros(10);  %matrice de 10 pe 10
% tic             %aflu cat dureaza iteratiile
% for i = 1:10
%     A(i,i) = 13;
% end
% toc
% 
% tic
% B = 13*eye(10); %eye e matrice identitate
% toc
% %whos A %detalii variabila A
% %A' transpusa
% 
% 
% syms x %simbolic
% f = @(x) x^3 + 2*x^2 + 3*x + 2;
% df = diff(f,x) derivata
% df = diff(f,x,2) derivata de ordin 2
% dppp=matlabFunction(f,x) handle

%%
%Rezolvam sistem de tipul A*x = b;
function [Abar] = test_v1(A,b)
for i = 1:length(A)
    if A(i,i)==0
        return;
    end
end
disp('Matricea aleasa este excelenta. MEG va functiona');

%Construiesc matricea extinsa/augmentata
Abar = [A,b];

%Construim matricea superior triunghiulara (cu zerouri sub diag. princ.)
for i = 1 : length(A)-1
    for j = i + 1 : length(A)
        m = Abar(j,i)/Abar(i,i);
        %L_j = L_j - m*L_i
        Abar(j,:) =  Abar(j,:) - m* Abar(i,:);
    end
end

%% Implementam substitutie descendenta

