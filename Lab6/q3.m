I=imread('img/lena.pgm');
[m,n]=size(I);
J=I;
for i=1:m
    for j=1:n
        J(i,j)=I(i,j)+20*sin(20*i)+20*sin(20*j);%增加周期性噪声
    end
end
IF=fftshift(fft2(I));
JF=fftshift(fft2(J));
IF=log(1+abs(IF));
JF=log(1+abs(JF));
figure(1)
subplot(121)%显示频谱
imshow(IF,[])
subplot(122)
imshow(JF,[])
%高斯带阻滤波器构造
fbrf=ones(m,n);
for i=1:m
    for j=1:n
        fbrf(i,j)=1-exp(-0.5*(((i-m/2)^2+(j-n/2)^2-55^2)/(sqrt(i.^2+j.^2)*5))^2);%20为带阻中心，5为带宽
    end
end
 H=fbrf;
%频率域滤波
f=fftshift(fft2(J));
out=f.*H;%频率域滤波
out=ifft2(ifftshift(out));
out=abs(out);
out=out/max(out(:));%归一化【0,1】
figure(2)
subplot(121)
imshow(out,[]);
subplot(122)
imshow(J,[])
w = waitforbuttonpress