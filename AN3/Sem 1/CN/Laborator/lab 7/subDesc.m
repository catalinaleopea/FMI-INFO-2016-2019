%Substitutie descendenta (cu produs scalar)
function [xNumeric] = subDesc(Abar)
xNumeric = zeros(length(Abar)-1,1);
for i = length(Abar)- 1 : 1
    xNumeric(i) = (Abar(i, length(Abar)) - Abar(i,i+1:length(Abar)-1)*...
        xNumeric(i+1,length(Abar), 1)) / Abar(i,i);
end
end