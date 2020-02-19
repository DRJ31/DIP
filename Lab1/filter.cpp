#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
  const char *file1 = "img/lena.pgm";
  const char *file2 = "img/noise.pgm";

  Mat srcImg1 = imread(file1);
  Mat srcImg2 = imread(file2);

  Mat outMedian1, outMedian2, outBlur1, outBlur2;

  medianBlur(srcImg1, outMedian1, 3);
  medianBlur(srcImg2, outMedian2, 3);
  blur(srcImg1, outBlur1, Size(3, 3));
  blur(srcImg2, outBlur2, Size(3, 3));

  imshow("Lena Median", outMedian1);
  imshow("Noise Median", outMedian2);
  imshow("Lena Average", outBlur1);
  imshow("Noise Average", outBlur2);

  waitKey(0);
  return 0;
}
