IMAGINI = struct('img',[],'proportie',[]);
%ex 1
imaginiFis = dir('data/*.jpeg');
nrImagini = length(imaginiFis);

%implementarea cerintelor pentru imaginea 1
%1
IMAGINI(1).img = imread('data/1.jpeg');
%imshow(IMAGINI(1).img);
%2
[height, width, c] = size(IMAGINI(1).img);
disp(height);
disp(width);
%3
propMax = height * width;
ImgRezMax = 1;
%4
IMAGINI(1).proportie = width / height;
difProportie = abs(1 - IMAGINI(1).proportie);
%disp(difProportie);
difProportieMin = difProportie;
ImgPropMin = 1;

%5 - calculeaza imaginea sepia pentru prima imagine
 for i=1:height
     for j=1:width
        R1 = floor ((0.393*IMAGINI(1).img(i,j,1)) + (0.769* IMAGINI(1).img(i,j,2)) + (0.189 * IMAGINI(1).img(i,j,3)));
        G1 = floor ((0.349*IMAGINI(1).img(i,j,1)) + (0.686* IMAGINI(1).img(i,j,2)) + (0.168 * IMAGINI(1).img(i,j,3)));
        B1 = floor ((0.272*IMAGINI(1).img(i,j,1)) + (0.534* IMAGINI(1).img(i,j,2)) + (0.131 * IMAGINI(1).img(i,j,3)));
        if R1>255
            R1 = 255;
        end
        if G1>255
            G1=255;
        end
        if B1>255
            B1=255;
        end
        IMAGINI(1).img(i,j,1)= R1;
        IMAGINI(1).img(i,j,2)= G1;
        IMAGINI(1).img(i,j,3)= B1;
     end
 end


%implementarea cerintelor pentru restul setului de imagini
  for i = 2:nrImagini
      %1 - citire
      IMAGINI(i).img = imread(['data/' imaginiFis(i).name]);
      % ex 2 - afisarea latinii si inaltimii
      [height, width, ~] = size(IMAGINI(i).img);
      disp(height);
      disp(width);
      % ex 3 - calculeaza rezolutia maxima
      resolution = height * width;
      if resolution > propMax 
          propMax = resolution;
          ImgRezMax = i;
      end
      % ex 4 - calculeaza proportia cea mai apropiata de 1
      IMAGINI(i).proportie = width / height;
      difProportie = abs(1 - IMAGINI(i).proportie);
      if difProportieMin > difProportie
          difProportieMin = difProportie;
          ImgPropMin = i;
      end
  end

%ex 3 - afiseaza imaginea cu rezolutia maxima
imshow(IMAGINI(ImgRezMax).img);
%ex 4 - afiseaza iamginea cu proportia cea mai apropiata de 1
imshow(IMAGINI(ImgPropMin).img);

