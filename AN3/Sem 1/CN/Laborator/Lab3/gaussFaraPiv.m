% Implementare MEG fara pivotare

function [xNumeric] = gaussFaraPiv(A, b)
tic 
B=[A, b']; %Matricea extinsa

%Ne asiguram ca nu avem elemente neutre pe linia pivotului 

for i = 1:length(b) %interschimbam liniile de pe/ sub coloana pivot 
    if B(i,i) == 0
       for j= i+1:length(b)
           if B(j,i) ~=0
               aux = B(i, :);
               B(i, :) = B(j, :);
               B(j, :) = aux;
               break;
           end
       end
    end
    
    
toc
end
disp(B)