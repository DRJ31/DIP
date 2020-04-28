
clear;
close all;
clc;

origin = imread('img/bubbles_on_black_background.pgm');
imshow(origin);title('原图');

%中值滤波去噪
filterResult = medfilt2(origin);
[m,n] = size(origin);
 
tmp = ~origin; 
figure,imshow(tmp);title('取反图像');

%空洞填充
fieldFilling = imfill(tmp,'holes');
figure, imshow(fieldFilling);title('区域填充');

boudaryGrains = origin;
for i = 1:m
    for j = 1:n
        if fieldFilling(i,j) == 1
            boudaryGrains(i,j) = 0;
        end
    end
end
figure, imshow(boudaryGrains);title('边界粒子');

%备用结构基元
se1 = strel('ball',12,11);
se2 = strel('disk',9);
se3 = ones(16,16);
se4 = strel('disk',11);

result1 = imerode(filterResult,se3);

result2 = medfilt2(result1);
result2 = filter2(fspecial('average',7),result2);
result2 = im2uint8(result2);
figure,imshow(result2);title('腐蚀结果');

result3 = imdilate(result2,se1);
figure,imshow(result3);title('膨胀结果');

%阈值处理
result4 = origin;
grayThreshhold = 8
for i = 1:m
    for j = 1:n
        if result3(i,j) <= grayThreshhold
            result4(i,j) = 0;
        end
    end
end
figure,imshow(result4);title('阈值处理');

%开启操作，平滑边界
result5 = imerode(result4,se2);
result6 = imdilate(result5,se4);
figure,imshow(result6);title('交叠粒子');

%单个粒子  
result7 = origin-result6-boudaryGrains;
result7 = imerode(result7,se3);
result7 = imdilate(result7,se4);
figure,imshow(result7);title('单个粒子');