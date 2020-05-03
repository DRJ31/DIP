#include "func.hpp"

using namespace cv;

void Question3()
{
  Mat src1 = imread("img/polymersomes.pgm");
  Mat src2 = imread("img/noisy_fingerprint.pgm");
  Mat dst1, dst2;

  // Original image
  imshow("Poly.jpg", src1);
  imshow("Finger.jpg", src2);
}