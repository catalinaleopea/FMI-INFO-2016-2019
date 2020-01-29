function imgSepia  = sepia( imagine )
    
[height, width, ~] = size(imagine);

for i=1:height
    for j=1:width
       R1 = floor ((0.393*imagine(i,j,1)) + (0.769* imagine(i,j,2)) + (0.189 * imagine(i,j,3)));
       G1 = floor ((0.349*imagine(i,j,1)) + (0.686* imagine(i,j,2)) + (0.168 * imagine(i,j,3)));
       B1 = floor ((0.272*imagine(i,j,1)) + (0.534* imagine(i,j,2)) + (0.131 * imagine(i,j,3)));
       if R1>255
           R1 = 255;
       end
       if G1>255
           G1=255;
       end
       if B1>255
           B1=255;
       end
       imagine(i,j,1)= R1;
       imagine(i,j,2)= G1;
       imagine(i,j,3)= B1;
    end
end

imgSepia = imagine;

end

