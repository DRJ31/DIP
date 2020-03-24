#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include "func.hpp"

#define BUFSIZE 512

using namespace std;
using namespace cv;


void gamma(Mat src, Mat &dst, double gval)
{
  vector<uchar> lut(256);
  vector<double> avg = {0,0,0}, sum = {0,0,0};
  dst = Mat(src.size(), src.type());

  for (int i = 0; i < 256; ++i) {
    lut[i] = round(pow(i / 255.0, gval) * 255);
  }

  for (int i = 0; i < src.size().height; ++i) {
    for (int j = 0; j < src.size().width; ++j) {
      for (int m = 0; m < 3; ++m) {
        dst.at<Vec3b>(i, j)[m] = lut[src.at<Vec3b>(i, j)[m]];
        avg[m] += dst.at<Vec3b>(i, j)[m];
      }
    }
  }

  for (int i = 0; i < 3; ++i)
    avg[i] /= src.size().height * src.size().width;

  for (int i = 0; i < src.size().height; ++i) {
    for (int j = 0; j < src.size().width; ++j) {
      for (int m = 0; m < 3; ++m) {
        sum[m] += pow(dst.at<Vec3b>(i, j)[m] - avg[m], 2);
      }
    }
  }

  for (int i = 0; i < 3; ++i) 
    sum[i] /= src.size().height * src.size().width;

  printf("The variance of gamma value %.1f is: %.2f\n", gval, sum[0] + sum[1] + sum[2] / 3);
}


void lab::Gamma(cv::String filename)
{
  Mat src = imread(filename);
  vector<double> gval = {0.1, 0.4, 0.6, 0.8, 1};
  Mat dst;
  char str[BUFSIZE];

  for (auto val : gval) {
    sprintf(str, "Gamma Value: %.1f", val);
    gamma(src, dst, val);
    imshow(str, dst);
  }
  
  imshow("Original Image", src);
  waitKey(0);
}