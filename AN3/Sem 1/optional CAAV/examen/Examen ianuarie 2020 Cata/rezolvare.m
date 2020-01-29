%Leopea Catalina, grupa 343

IMAGINISOCCERBALL = struct('img',[],'eticheta',[]);
IMAGINITESTSOCCERBALL = struct('img',[],'eticheta',[]);

%citeste imaginile de antrenare din clasa 0: soccer_ball
imaginiAntrenareSoccerBall = dir('../soccer_ball/*.jpg');
nrImaginiAntrenareSoccerBall = length(imaginiAntrenareSoccerBall);
medieGrayscaleSoccerBall = zeros(1,nrImaginiAntrenareSoccerBall);
nrImaginiGrayscale = 0;
nrImaginiColor = 0;

for i = 1:45
    IMAGINISOCCERBALL(i).img = imread(['../soccer_ball/' imaginiAntrenareSoccerBall(i).name]);    
    IMAGINISOCCERBALL(i).eticheta = 0; %imaginile cu mingi de fotbal au eticheta 0 
    IMAGINISOCCERBALL(i).medieGrayscale = 0;
    if size(IMAGINISOCCERBALL(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINISOCCERBALL(i).img);
        IMAGINISOCCERBALL(i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColor = nrImaginiColor + 1;
    else
        if size(IMAGINISOCCERBALL(i).img,3) == 1
            IMAGINISOCCERBALL(i).medieGrayscale = mean(mean(IMAGINISOCCERBALL(i).img));
            nrImaginiGrayscale = nrImaginiGrayscale + 1;
        end
    end
    medieGrayscaleSoccerBall(i) = IMAGINISOCCERBALL(i).medieGrayscale;
end

%citeste imaginile de test din clasa 0: soccer_ball
for i = 1:15
    IMAGINITESTSOCCERBALL(i).img = imread(['../soccer_ball/' imaginiAntrenareSoccerBall(i+45).name]);    
    IMAGINITESTSOCCERBALL(i).eticheta = 0; %imaginile cu mingi de fotbal au eticheta 0 
    IMAGINITESTSOCCERBALL(i).medieGrayscale = 0;
    if size(IMAGINITESTSOCCERBALL(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINITESTSOCCERBALL(i).img);
        IMAGINITESTSOCCERBALL(i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColor = nrImaginiColor + 1;
    else
        if size(IMAGINITESTSOCCERBALL(i).img,3) == 1
            IMAGINITESTSOCCERBALL(i).medieGrayscale = mean(mean(IMAGINITESTSOCCERBALL(i).img));
            nrImaginiGrayscale = nrImaginiGrayscale + 1;
        end
    end
    medieGrayscaleSoccerBall(i+45) = IMAGINITESTSOCCERBALL(i).medieGrayscale;
end


IMAGINIDALMATIAN = struct('img',[],'eticheta',[]);
IMAGINITESTDALMATIAN = struct('img',[],'eticheta',[]);

%citeste imaginile de antrenare din clasa 1: dalmatian
imaginiAntrenareDalmatian = dir('../dalmatian/*.jpg');
nrImaginiAntrenareDalmatian = length(imaginiAntrenareDalmatian);
medieGrayscaleDalmatian = zeros(1,nrImaginiAntrenareDalmatian);
nrImaginiGrayscaleDalmatian = 0;
nrImaginiColorDalmatian = 0;

for i = 1 : 45
    IMAGINIDALMATIAN(i).img = imread(['../dalmatian/' imaginiAntrenareDalmatian(i).name]);    
    IMAGINIDALMATIAN(i).eticheta = 1; %imaginile cu dalmatieni au eticheta 1
    IMAGINIDALMATIAN(i).medieGrayscale = 0; 
    if size(IMAGINIDALMATIAN(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINIDALMATIAN(i).img);
        IMAGINIDALMATIAN(i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColorDalmatian = nrImaginiColorDalmatian + 1;
    else
        if size(IMAGINIDALMATIAN(i).img,3) == 1
            IMAGINIDALMATIAN(i).medieGrayscale = mean(mean(IMAGINIDALMATIAN(i).img));
            nrImaginiGrayscaleDalmatian = nrImaginiGrayscaleDalmatian + 1;
        end
    end
    medieGrayscaleDalmatian(i) =  IMAGINIDALMATIAN(i).medieGrayscale;
end

%citeste imaginile de test din clasa 1: dalmatian
for i = 1:15
    IMAGINITESTDALMATIAN(i).img = imread(['../soccer_ball/' imaginiAntrenareDalmatian(i+45).name]);    
    IMAGINITESTDALMATIAN(i).eticheta = 1;
    IMAGINITESTDALMATIAN(i).medieGrayscale = 0;
    if size(IMAGINITESTDALMATIAN(i).img,3) == 3
        imgTemp = rgb2gray(IMAGINITESTDALMATIAN(i).img);
        IMAGINITESTDALMATIAN(i).medieGrayscale = mean(mean(imgTemp));
        nrImaginiColor = nrImaginiColor + 1;
    else
        if size(IMAGINITESTDALMATIAN(i).img,3) == 1
            IMAGINITESTDALMATIAN(i).medieGrayscale = mean(mean(IMAGINITESTDALMATIAN(i).img));
            nrImaginiGrayscale = nrImaginiGrayscale + 1;
        end
    end
    medieGrayscaleDalmatian(i+45) = IMAGINITESTDALMATIAN(i).medieGrayscale;
end
%clasificare folosind media grayscale
parametru.medieSoccerBall = mean(medieGrayscaleSoccerBall);
parametru.medieDalmatian = mean(medieGrayscaleDalmatian);
parametru.img = IMAGINIDALMATIAN(2).img;
rezultat = clasificareImagineMedieGrayscale(parametru);
fprintf(" Rezultat clasificare = %d\n",rezultat);

acurateteSoccerBall = zeros(1,45);
for i=1:45
    parametru.img = IMAGINISOCCERBALL(i).img;
    acurateteSoccerBall(i) = clasificareImagineMedieGrayscale(parametru);
end
fprintf("gasite bine = %d\n", sum(acurateteSoccerBall));
procentAcurateteSoccerBall = (sum(acurateteSoccerBall)*100)/45;
fprintf("Procent Acuratete SoccerBall = %d\n", procentAcurateteSoccerBall);

acurateteSoccerBallTot = zeros(1,60);
for i=1:45
    parametru.img = IMAGINISOCCERBALL(i).img;
    acurateteSoccerBallTot(i) = clasificareImagineMedieGrayscale(parametru);
end
for i=1:15
    parametru.img = IMAGINITESTDALMATIAN(i).img;
    acurateteSoccerBallTot(i+45) = clasificareImagineMedieGrayscale(parametru);
end
fprintf("gasite bine = %d\n", sum(acurateteSoccerBallTot));
procentAcurateteSoccerBallTot = (sum(acurateteSoccerBallTot)*100)/60;
fprintf("Procent Acuratete SoccerBall = %d\n", procentAcurateteSoccerBallTot);

acurateteDalmatian = zeros(1,45);
for i=1:45
    parametru.img = IMAGINIDALMATIAN(i).img;
    acurateteDalmatian(i) = clasificareImagineMedieGrayscale(parametru);
end
fprintf("gasite bine = %d\n", 45 - sum(acurateteDalmatian));
procentAcurateteDalmatian = (45 - sum(acurateteDalmatian))*100/45;
fprintf("Procent Acuratete Dalmatian = %d\n",procentAcurateteDalmatian);

acurateteDalmatianTot = zeros(1,60);
for i=1:45
    parametru.img = IMAGINIDALMATIAN(i).img;
    acurateteDalmatianTot(i) = clasificareImagineMedieGrayscale(parametru);
end
for i=1:15
    parametru.img = IMAGINITESTDALMATIAN(i).img;
    acurateteDalmatianTot(i+45) = clasificareImagineMedieGrayscale(parametru);
end
fprintf("gasite bine = %d\n", 60 - sum(acurateteDalmatianTot));
procentAcurateteDalmatian = (60 - sum(acurateteDalmatianTot))*100/60;
fprintf("Procent Acuratete Dalmatian tot = %d\n",procentAcurateteDalmatian);