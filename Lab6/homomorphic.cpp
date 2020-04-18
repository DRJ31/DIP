#include <iostream>
#include <cmath>
#include "operations.hpp"
#include "func.hpp"

using namespace std;
using namespace cv;

void homoFilter(Mat src, Mat &dst)
{
    
  src.convertTo(src, CV_64FC1);
  dst.convertTo(dst, CV_64FC1);

  //1. ln
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j){
      src.at<double>(i, j) = log(src.at<double>(i, j) + 1);
    }
  }
    
  //spectrum
  //2. dct
  Mat mat_dct = Mat(src.size(), CV_64FC1);
  dct(src, mat_dct);
  
  //3. linear filter
  Mat linear_filter;
  double gammaH = 1.5;
  double gammaL = 0.5;
  double C = 1;
  double d0 = (src.rows / 2) * (src.rows / 2) + (src.cols / 2) * (src.cols / 2);
  double d2 = 0;
  linear_filter = Mat(src.size(), CV_64FC1);
  
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      d2 = i * i + j * j;
      linear_filter.at<double>(i, j) = 	(gammaH - gammaL) * (1 - exp(-C * d2 / d0)) + gammaL;
    }
  }
  linear_filter.ptr<double>(0)[0] = 1.1;

  mat_dct = mat_dct.mul(linear_filter);

  //4. idct
  idct(mat_dct, dst);
  
  //5. exp
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      dst.at<double>(i, j) = exp(dst.at<double>(i, j));
    }
  }
  
  dst.convertTo(dst, CV_8UC1);
}

void lab::HomomorphicFilter(cv::String filename)
{
  Mat src = imread(filename, 0);
  imshow("src", src);
  Mat dst = Mat(src.size(), src.type());
  homoFilter(src, dst);
  imshow("dst", dst);
  imwrite("dst.jpg", dst);
}