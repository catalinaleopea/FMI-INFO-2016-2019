function eticheta = clasificareImagineTestare( parametru )
%ex5
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
    distSB = (abs(medieImg-parametru.medieSB));
    distYY = (abs(medieImg-parametru.medieYY));
    if distSB > distYY
        eticheta = 1;
    else
        eticheta = 2;
    end
end
end