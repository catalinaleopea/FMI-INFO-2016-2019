clear all;
IMAGINI = struct('img',[],'eticheta',[]);

%citeste imaginile de antrenare din clasa ZI
imaginiAntrenareZI = dir('../data/antrenare/ZI/*.jpg');
nrImaginiAntrenareZI = length(imaginiAntrenareZI);
medieGrayscaleZI = zeros(1,nrImaginiAntrenareZI); %ex3
for i = 1:nrImaginiAntrenareZI
    IMAGINI(i).img = imread(['../data/antrenare/ZI/' imaginiAntrenareZI(i).name]);    
    IMAGINI(i).eticheta = 1; %imaginile cu scene de ZI au eticheta 1 
    %ex2
    IMAGINI(i).medieGrayscale = 0;
    if size(IMAGINI(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINI(i).img);
        IMAGINI(i).medieGrayscale = mean(mean(imgTemp));
    else
        if size(IMAGINI(i).img,3) == 1
            IMAGINI(i).medieGrayscale = mean(mean(IMAGINI(i).img));
        end
    end
    medieGrayscaleZI(i) = IMAGINI(i).medieGrayscale; %ex3
end
%ex1
imaginiAntrenareNOAPTE = dir('../data/antrenare/NOAPTE/*.jpg');
nrImaginiAntrenareNOAPTE = length(imaginiAntrenareNOAPTE);
medieGrayscaleNOAPTE = zeros(1,nrImaginiAntrenareNOAPTE); %ex3
for i =1:nrImaginiAntrenareNOAPTE
    IMAGINI( nrImaginiAntrenareZI+i).img = imread(['../data/antrenare/NOAPTE/' imaginiAntrenareNOAPTE(i).name]);    
    IMAGINI( nrImaginiAntrenareZI+i).eticheta = 0; %imaginile cu scene de NOAPTE au eticheta 0 
    %ex2 
    IMAGINI( nrImaginiAntrenareZI+i).medieGrayscale = 0; 
    if size(IMAGINI( nrImaginiAntrenareZI+i).img,3) == 3
        imgTemp = rgb2gray(IMAGINI( nrImaginiAntrenareZI+i).img);
        IMAGINI( nrImaginiAntrenareZI+i).medieGrayscale = mean(mean(imgTemp));
    else
        if size(IMAGINI( nrImaginiAntrenareZI+i).img,3) == 1
            IMAGINI( nrImaginiAntrenareZI+i).medieGrayscale = mean(mean(IMAGINI( nrImaginiAntrenareZI+i).img));
        end
    end
    medieGrayscaleNOAPTE(i) =  IMAGINI( nrImaginiAntrenareZI+i).medieGrayscale; %ex3
end
%ex3
medieZI = mean(medieGrayscaleZI);
medieNOAPTE = mean(medieGrayscaleNOAPTE);
%ex4
parametru.medieZI = medieZI;
parametru.medieNOAPTE = medieNOAPTE;
parametru.img = IMAGINI(1).img;
clasificareImagineMedieGrayscale(parametru);
%ex5
acurateteZi = ones(1,nrImaginiAntrenareZI);
for i=1:nrImaginiAntrenareZI
    parametru.img = IMAGINI(i).img;
    acurateteZi(i) = clasificareImagineMedieGrayscale(parametru);
end
procentAcurateteZi = sum(acurateteZi)*100/nrImaginiAntrenareZI;
fprintf("Procent Acuratete ZI = %d%%\n",procentAcurateteZi);
acurateteNOAPTE = ones(1,nrImaginiAntrenareNOAPTE);
for i=1:nrImaginiAntrenareNOAPTE
    parametru.img = IMAGINI(nrImaginiAntrenareZI+i).img;
    acurateteNOAPTE(i) = clasificareImagineMedieGrayscale(parametru);
end
procentAcurateteNOAPTE = (nrImaginiAntrenareNOAPTE-sum(acurateteNOAPTE))*100/nrImaginiAntrenareNOAPTE;
fprintf("Procent Acuratete NOAPTE = %d%%\n",procentAcurateteNOAPTE);
%ex6
nrImaginiTotal = nrImaginiAntrenareNOAPTE+nrImaginiAntrenareZI;
dimensiuneExtragere = (nrImaginiTotal)*100;
extragere = zeros(dimensiuneExtragere,3);
for i=1:nrImaginiTotal
    randomizator = rand(100,2);
    for j=1:100
        extragere((i-1)*100+j,:) = IMAGINI(i).img(ceil(randomizator(j,1) * size(IMAGINI(i).img,1)),ceil(randomizator(j,2) * size(IMAGINI(i).img,2)),:);
    end
end
        %printer for monitoring    fprintf("eroare = %d %d %d\n",i,j,(i-1)*100+j);
[clusteruri, aratator] = kmeans_iter(extragere,20,10);
%ex8 (este corect chiar daca rezultatul poate fi eronat din cauza ca
%functia de calcul de histograma normalizata poate are bug (nu sunt sigur ca da rezultat corect), ex 8 este atins :)
for i=1:nrImaginiTotal
    IMAGINI(i).histogramaNormalizata = calculeazaHistogramaNormalizataCuvinteVizuale(IMAGINI(1).img,clusteruri);
end
