function eticheta = clasificareImagineMedieGrayscale( parametru )
%ex4
eticheta = -1;
ok=1;
if size(parametru.img,3) == 3
    imgTemp = rgb2gray(parametru.img);
else
    if size(parametru.img,3) == 1
        imgTemp = parametru.img;
    else
        eticheta = -1;
        ok=0;
    end
end
if ok==1
    medieImg = mean(mean(imgTemp));
    distZi = (abs(medieImg-parametru.medieZI));
    distNOAPTE = (abs(medieImg-parametru.medieNOAPTE));
    if distZi > distNOAPTE
        eticheta = 0;
    else
        eticheta = 1;
    end
end
end

