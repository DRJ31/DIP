#include "func.hpp"

using namespace cv;
using namespace lab;

void lab::NoiseCancel()
{
  Mat src1 = imread("img/LenaWithNoise.pgm", 0);
  Mat src2 = imread("img/cameraWithNoise.pgm", 0);
  Mat dst1 = Mat(src1.size(), CV_8UC1);
  Mat dst2 = Mat(src2.size(), CV_8UC1);
  
  Filter<uchar>::convolution(src1, dst1, Size(4, 4), Filter<uchar>::median);
  Filter<uchar>::convolution(src2, dst2, Size(4, 4), Filter<uchar>::median);

  imshow("lena.pgm", src1);
  imshow("camera.pgm", src2);
  imshow("lenaFiltered.jpg", dst1);
  imshow("cameraFiltered.jpg", dst2);
}