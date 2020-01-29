%Ex 3

%Sa rulam pe gpu testat pt optimizari

function [xNumeric] = gaussFaraPivotare(A, b)
    B = [A, b'];%Matricea extinsa
    %coafam matricea, ne asiguram ca nu avem elemente neutre pe linia
    %pivotului
    for i = 1:length(b)
        if B(i, i) == 0
            for j = i + 1:length(b)
                if B(j, i) ~= 0
                    aux = B(i, :);
                    B(i, :) = B(j, :);
                    B(j, :) = aux;
                    break;
                end
            end
        end
    end
    disp(B);
end 