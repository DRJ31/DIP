#include <cmath>
#include "func.hpp"

#define ROBERTS 1
#define SOBEL   2
#define PREWITT 3

using namespace cv;
using namespace std;


/* Get value from Mat */
double getValue(Mat src, int x, int y) {
  return (double) x < 0 || y < 0 || x >= src.rows || y >= src.cols ? 0 : src.at<uchar>(x, y);
}


/* Gaussian filter */
uchar gaussian(int x, int y, Mat tmp, Size ksize, double sigma)
{
  double result = 0;
  double d0 = 2 * sigma * sigma;
  for (int i = x; i < ksize.height + x; ++i) {
    for (int j = y; j < ksize.width + y; ++j) {
      int x0 = i - x - ksize.height / 2;
      int y0 = j - y - ksize.width / 2;
      double d = (double)(x0 * x0 + y0 * y0);
      result += (double)tmp.at<uchar>(i, j) * exp(-d / d0) / (d0 * PI);
    }
  }
  return (uchar)result;
}


/* Intensity gradient */
vector<uchar> intensityGradient(int x, int y, Mat tmp, Size ksize, int filterType)
{
  vector<int> kernelX, kernelY;
  vector<uchar> results;
  double resultX = 0, resultY = 0;

  // Decide kernel according to algorithms
  if (filterType == 1) {
    kernelX = {1, 0, 0, 0, -1, 0, 0, 0, 0};
    kernelY = {0, 1, 0, -1, 0, 0, 0, 0, 0};
  } else if (filterType == 2) {
    kernelX = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    kernelY = {1, 2, 1, 0, 0, 0, -1, -2, -1};
  } else {
    kernelX = {1, 0, -1, 1, 0, -1, 1, 0, -1};
    kernelY = {1, 1, 1, 0, 0, 0, -1, -1, -1};
  }

  for (int i = x; i < x + ksize.height; ++i) {
    for (int j = y; j < y + ksize.width; ++j) {
      int pos = (i - x) * ksize.width + (j - y);
      resultX += kernelX[pos] * (int)tmp.at<uchar>(i, j);
      resultY += kernelY[pos] * (int)tmp.at<uchar>(i, j);
    }
  }

  // Add to results
  results.push_back((uchar)sqrt(resultX * resultX + resultY * resultY));
  results.push_back((uchar)resultX);
  results.push_back((uchar)resultY);

  return results;
}


// Non-maximum Suppresion
uchar nms(int x, int y, Mat d, Mat dx, Mat dy)
{
  double gradTmp = (double)d.at<uchar>(x, y);
  if (gradTmp == 0)
    return 0;

  double gradX = (double)dx.at<uchar>(x, y), gradY = (double)dy.at<uchar>(x, y);
  double grad1, grad2, grad3, grad4, weight, gradTmp1, gradTmp2;

  if (abs(gradY) > abs(gradX)) {
    weight = abs(gradX) / abs(gradY);
    grad2 = getValue(d, x - 1, y);
    grad4 = getValue(d, x + 1, y);
    if (gradX * gradY > 0) {
      grad1 = getValue(d, x - 1, y - 1);
      grad3 = getValue(d, x + 1, y + 1);
    } else {
      grad1 = getValue(d, x - 1, y + 1);
      grad3 = getValue(d, x + 1, y - 1);
    }
  } else {
    weight = abs(gradY) / abs(gradX);
    grad2 = getValue(d, x, y - 1);
    grad4 = getValue(d, x, y + 1);
    if (gradX * gradY > 0) {
      grad1 = getValue(d, x + 1, y - 1);
      grad3 = getValue(d, x - 1, y + 1);
    } else {
      grad1 = getValue(d, x - 1, y - 1);
      grad3 = getValue(d, x + 1, y + 1);
    }
  }

  gradTmp1 = weight * grad1 + (1-weight) * grad2;
  gradTmp2 = weight * grad3 + (1-weight) * grad4;
  return gradTmp >= gradTmp1 && gradTmp >= gradTmp2 ? (uchar)gradTmp : 0;
}


/* Double Threshold */
void doubleThreshold(Mat src, Mat &dst, double rate1, double rate2)
{
  Mat thr1, thr2;
  dst = Mat(src.size(), src.type());

  // Threshold by 2 different rate
  lab::threshold(src, thr1, rate1 * 255);
  lab::threshold(src, thr2, rate2 * 255);

  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      dst.at<uchar>(i, j) = thr1.at<uchar>(i, j) && thr2.at<uchar>(i, j) ? 255 : 0;
    }
  }
}


/* Main logic of Canny */
void canny(Mat src, Mat &dst, Size ksize, double sigma, int filterType, double thrLow, double thrHigh)
{
  dst = Mat(src.size(), src.type());
  Mat d, dx, dy;

  // Gaussian
  lab::convolution(src, dst, ksize, sigma, gaussian);

  // Intensity gradient
  lab::convolution(src, d, dx, dy, ksize, filterType, intensityGradient);

  // Non-maximum Suppresion
  lab::convolution(d, dx, dy, dst, nms);

  // Double Threshold
  doubleThreshold(dst, dst, thrLow, thrHigh);
}


/* Laplacian Operator */
uchar laplacian(int x, int y, Mat tmp, Size ksize)
{
  double result = 0;
  vector<int> kernel = {0, 1, 0, 1, -4, 1, 0, 1, 0};

  for (int i = x; i < ksize.height + x; ++i) {
    for (int j = y; j < ksize.width + y; ++j) {
      int pos = (i - x) * ksize.width + j - y;
      result += tmp.at<uchar>(i, j) * kernel[pos];
    }
  }

  return (uchar)result / (ksize.height * ksize.width); 
}


/* Laplacian of Gaussian */
void LoG(Mat src, Mat &dst, Size ksize, double sigma) 
{
  lab::convolution(src, dst, ksize, sigma, gaussian);
  lab::convolution(dst, dst, ksize, laplacian);
}


/* Main logic of Question2 */
void Question2()
{
  Mat src1 = imread("img/headCT-Vandy.pgm", 0);
  Mat src2 = imread("img/noisy_fingerprint.pgm", 0);
  Mat dst1, dst2;

  // Original image
  imshow("CT.jpg", src1);
  imshow("Finger.jpg", src2);

  // Canny operation
  canny(src1, dst1, Size(3, 3), 1, ROBERTS, 0.2, 0.3);
  canny(src2, dst2, Size(3, 3), 1, ROBERTS, 0.2, 0.3);

  imshow("CannyCT.jpg", dst1);
  imshow("CannyFinger.jpg", dst2);

  // Laplacian of Gaussian operation
  LoG(src1, dst1, Size(3, 3), 1);
  LoG(src2, dst2, Size(3, 3), 1);

  imshow("LoGCT.jpg", dst1);
  imshow("LoGFinger.jpg", dst2);
}