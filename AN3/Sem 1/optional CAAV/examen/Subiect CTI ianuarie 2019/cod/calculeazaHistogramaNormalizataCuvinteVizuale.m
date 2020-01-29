function histogramaNormalizata = calculeazaHistogramaNormalizataCuvinteVizuale( img,D )
%ex7
histograma = zeros(size(D,1),size(D,1),size(D,1));
cR = img(:,:,1);
cG = img(:,:,2);
cB = img(:,:,3);
imgN = [cR(:) cG(:) cB(:)];
for i=1:size(imgN,1)
    distantex = zeros(size(D,1));
    for j=1:size(D,1)
        distantex(j) = abs(imgN(i,1)-D(j,1));
    end
    idx = find(distantex==min(distantex),1);
    distantey = zeros(size(D,1));
    for j=1:size(D,1)
        distantey(j) = abs(imgN(i,2)-D(j,2));
    end
    idy = find(distantey==min(distantey),1);
    distantez = zeros(size(D,1));
    for j=1:size(D,1)
        distantez(j) = abs(imgN(i,3)-D(j,3));
    end
    idz = find(distantez==min(distantez),1);
    histograma(idx,idy,idz)=histograma(idx,idy,idz)+1;
end
histograma = histograma(:);
histograma = histograma ./ sum(sum(histograma));
histogramaNormalizata = histograma;
end

