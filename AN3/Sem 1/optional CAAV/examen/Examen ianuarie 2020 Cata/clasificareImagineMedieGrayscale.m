%calculeaza media x a intensitatii pixelilor din imaginea grayscale
%obtinuta si daca x e mai aproape (distanta euclidiana) de medie soccer
%ball intoarce 1 altfel intoarce 0 
function eticheta = clasificareImagineMedieGrayscale( parametru )
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
    distSoccerBall = (abs(medieImg-parametru.medieSoccerBall));
    distDalmatian = (abs(medieImg-parametru.medieDalmatian));
    if distSoccerBall > distDalmatian
        eticheta = 0;
    else
        eticheta = 1;
    end
end
end
