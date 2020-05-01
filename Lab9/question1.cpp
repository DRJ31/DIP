#include <vector>
#include <cmath>
#include "func.hpp"

using namespace cv;
using namespace std;

uchar roberts(int x, int y, Mat tmp, Size ksize)
{
  vector<int> kernelX = {1, 0, 0, 0, -1, 0, 0, 0, 0};
  vector<int> kernelY = {0, 1, 0, -1, 0, 0, 0, 0, 0};
  double resultX = 0, resultY = 0;

  for (int i = x; i < x + ksize.height; ++i) {
    for (int j = y; j < y + ksize.width; ++j) {
      int pos = (i - x) * ksize.width + (j - y);
      resultX += kernelX[pos] * (int)tmp.at<uchar>(i, j);
      resultY += kernelY[pos] * (int)tmp.at<uchar>(i, j);
    }
  }

  return (uchar)sqrt(resultX * resultX + resultY * resultY);
}

uchar sobel(int x, int y, Mat tmp, Size ksize)
{
  vector<int> kernelX = {1, 0, -1, 2, 0, -2, 1, 0, -1};
  vector<int> kernelY = {1, 2, 1, 0, 0, 0, -1, -2, -1};
  double resultX = 0, resultY = 0;

  for (int i = x; i < x + ksize.height; ++i) {
    for (int j = y; j < y + ksize.width; ++j) {
      int pos = (i - x) * ksize.width + (j - y);
      resultX += kernelX[pos] * (int)tmp.at<uchar>(i, j);
      resultY += kernelY[pos] * (int)tmp.at<uchar>(i, j);
    }
  }

  return (uchar)sqrt(resultX * resultX + resultY * resultY);
}

uchar prewitt(int x, int y, Mat tmp, Size ksize)
{
  vector<int> kernelX = {1, 0, -1, 1, 0, -1, 1, 0, -1};
  vector<int> kernelY = {1, 1, 1, 0, 0, 0, -1, -1, -1};
  double resultX = 0, resultY = 0;

  for (int i = x; i < x + ksize.height; ++i) {
    for (int j = y; j < y + ksize.width; ++j) {
      int pos = (i - x) * ksize.width + (j - y);
      resultX += kernelX[pos] * (int)tmp.at<uchar>(i, j);
      resultY += kernelY[pos] * (int)tmp.at<uchar>(i, j);
    }
  }

  return (uchar)sqrt(resultX * resultX + resultY * resultY);
}

void Question1()
{
  Mat src1 = imread("img/headCT-Vandy.pgm", 0);
  Mat src2 = imread("img/building_original.pgm", 0);
  Mat src3 = imread("img/noisy_fingerprint.pgm", 0);
  Mat dst1, dst2, dst3;

  // Original image
  imshow("CT.jpg", src1);
  imshow("building.jpg", src2);
  imshow("finger.jpg", src3);

  // Roberts
  lab::convolution(src1, dst1, Size(3, 3), roberts);
  lab::convolution(src2, dst2, Size(3, 3), roberts);
  lab::convolution(src3, dst3, Size(3, 3), roberts);
  imshow("RobertsCT.jpg", dst1);
  imshow("RobertsBuilding.jpg", dst2);
  imshow("RobertsFinger.jpg", dst3);

  // Sobel
  lab::convolution(src1, dst1, Size(3, 3), sobel);
  lab::convolution(src2, dst2, Size(3, 3), sobel);
  lab::convolution(src3, dst3, Size(3, 3), sobel);
  imshow("SobelCT.jpg", dst1);
  imshow("SobelBuilding.jpg", dst2);
  imshow("SobelFinger.jpg", dst3);

  // Prewitt
  lab::convolution(src1, dst1, Size(3, 3), prewitt);
  lab::convolution(src2, dst2, Size(3, 3), prewitt);
  lab::convolution(src3, dst3, Size(3, 3), prewitt);
  imshow("PrewittCT.jpg", dst1);
  imshow("PrewittBuilding.jpg", dst2);
  imshow("PrewittFinger.jpg", dst3);
}