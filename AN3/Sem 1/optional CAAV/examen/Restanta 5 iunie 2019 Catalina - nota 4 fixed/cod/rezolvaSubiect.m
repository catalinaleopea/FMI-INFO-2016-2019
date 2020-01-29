%Leopea Catalina, grupa 343

IMAGINI = struct('img',[],'eticheta',[]);
IMAGINITEST = struct('img',[],'eticheta',[]);

numeImaginiTestare = dir('../data/imaginiTestare/*.jpg');
nrImaginiTestare = length(numeImaginiTestare);
imgTestare = cell(1,nrImaginiTestare);
for i =1:nrImaginiTestare
    imgTestare{i} = imread(['../data/imaginiTestare/' numeImaginiTestare(i).name]);
    
    IMAGINITEST(i).img =imread(['../data/imaginiTestare/' numeImaginiTestare(i).name]);
    IMAGINITEST(i).eticheta = 1;
end

x=[1,4,5,8,10,12,13,15,17,19];
for i = 1:length(x)
    IMAGINITEST(x(i)).eticheta = 2;
end

%citeste imaginile de antrenare din clasa 1: soccer_ball
imaginiAntrenareSoccerBall = dir('../data/soccer_ball/*.jpg');
nrImaginiAntrenareSoccerBall = length(imaginiAntrenareSoccerBall);
medieGrayscaleSoccerBall = zeros(1,nrImaginiAntrenareSoccerBall);
nrImaginiGrayscale = 0;
nrImaginiColor = 0;

for i = 1:nrImaginiAntrenareSoccerBall
    IMAGINI(i).img = imread(['../data/soccer_ball/' imaginiAntrenareSoccerBall(i).name]);    
    IMAGINI(i).eticheta = 1; %imaginile cu mingi de fotbal au eticheta 1 
    %imshow( IMAGINI(i).img);
    %ex2
    IMAGINI(i).medieGrayscale = 0;
    if size(IMAGINI(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINI(i).img);
        IMAGINI(i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColor = nrImaginiColor + 1;
    else
        if size(IMAGINI(i).img,3) == 1
            IMAGINI(i).medieGrayscale = mean(mean(IMAGINI(i).img));
            nrImaginiGrayscale = nrImaginiGrayscale + 1;
        end
    end
    medieGrayscaleSoccerBall(i) = IMAGINI(i).medieGrayscale;
end
fprintf("Dir soccer_ball : Nr imagini grayscale = %d\n",nrImaginiGrayscale);
fprintf("Nr imagini color = %d\n",nrImaginiColor);
    
%citeste imaginile de antrenare din clasa 2: yin_yang
imaginiAntrenareYinYang = dir('../data/yin_yang/*.jpg');
nrImaginiAntrenareYinYang = length(imaginiAntrenareYinYang);
medieGrayscaleYinYang = zeros(1,nrImaginiAntrenareYinYang);
nrImaginiGrayscale2 = 0;
nrImaginiColor2 = 0;

for i =1:nrImaginiAntrenareYinYang
    IMAGINI( nrImaginiAntrenareSoccerBall+i).img = imread(['../data/yin_yang/' imaginiAntrenareYinYang(i).name]);    
    IMAGINI( nrImaginiAntrenareSoccerBall+i).eticheta = 2;
    %imaginile cu simbolul yin yang au eticheta 2
    %ex2 
    IMAGINI( nrImaginiAntrenareSoccerBall+i).medieGrayscale = 0; 
    if size(IMAGINI( nrImaginiAntrenareSoccerBall+i).img,3) == 3
        imgTemp = rgb2gray(IMAGINI( nrImaginiAntrenareSoccerBall+i).img);
        IMAGINI( nrImaginiAntrenareSoccerBall+i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColor2 = nrImaginiColor2 + 1;
    else
        if size(IMAGINI( nrImaginiAntrenareSoccerBall+i).img,3) == 1
            IMAGINI( nrImaginiAntrenareSoccerBall+i).medieGrayscale = mean(mean(IMAGINI( nrImaginiAntrenareSoccerBall+i).img));
            nrImaginiGrayscale2 = nrImaginiGrayscale2 + 1;
        end
    end
    medieGrayscaleYinYang(i) =  IMAGINI( nrImaginiAntrenareSoccerBall+i).medieGrayscale;
end
fprintf('Dir yin_yang : Nr imagini grayscale = %d\n',nrImaginiGrayscale2);
fprintf('Nr imagini color = %d\n',nrImaginiColor2);
    
%ex 3
param.img = rgb2gray(IMAGINI(1).img);
param.nrIntervale = 5;
calculeazaHistogramaGri(param);

%ex4
i1=IMAGINI(1).img;
i1=i1(:,:,1);
[c1,n]=imhist(i1);
c1=c1/size(i1,1)/size(i1,2); 

i2=IMAGINI(2).img;
i2=i2(:,:,1);
[c2,n2]=imhist(i2);
c2=c2/size(i2,1)/size(i2,2);
fprintf('Distanta = %d\n',pdist2(c1',c2'));

%ex 5
medieSB = mean(medieGrayscaleSoccerBall);
medieYY = mean(medieGrayscaleYinYang);
parametru.medieSB = medieSB;
parametru.medieYY = medieYY;
parametru.img = IMAGINITEST(1).img;
clasificareImagineTestare(parametru);

acurateteTest = ones(1,nrImaginiTestare);
for i=1:nrImaginiTestare
    parametru.img = IMAGINITEST(i).img;
    acurateteTest(i) = clasificareImagineTestare(parametru);
end
procentAcurateteTestare = sum(acurateteTest)*100/nrImaginiTestare;
fprintf("Procent Acuratete = %d\n",procentAcurateteTestare);
