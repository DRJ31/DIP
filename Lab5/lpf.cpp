#include <iostream>
#include <string>
#include "func.hpp"
#include "operations.hpp"

using namespace std;
using namespace cv;

// Frequency domain filtering
Mat frequency_filter(Mat src, Mat kernel)
{
  Mat dst1, dst2;

  lab::dft(src, dst1, dst2);
  
  lab::shift(dst1, dst1);
  lab::shift(dst2, dst2);

	Mat blur_r,blur_i,BLUR;
  multiply(dst1, kernel, dst1); 
  multiply(dst2, kernel, dst2); 
  lab::magnitude(dst1, dst2, dst1);

  lab::idft(dst1, dst1, dst2);
  lab::magnitude(dst1, dst2, dst1);
  // dst += 1;
  // lab::log(dst, dst);
  lab::normalize(dst1, dst1);
  cout << "Done" << endl;
  return dst1;
}

Mat ideal_low_kernel(Mat src,double sigma)
{
  Mat ideal_low_pass(src.size(),CV_64FC1); 
  double d0 = sigma;
  for (int i = 0;i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
      if (d <= d0) {
        ideal_low_pass.at<double>(i,j) = 1;
      } else {
        ideal_low_pass.at<double>(i,j) = 0;
      }
    }
  }
  cv::String name = cv::format("IDLPF d0=%.1f", sigma);
  imshow(name, ideal_low_pass);
  return ideal_low_pass;
}

// Ideal low pass filter
Mat lab::ideal_low_pass_filter(Mat src, double sigma)
{

  Mat ideal_kernel = ideal_low_kernel(src, sigma);
  Mat result = frequency_filter(src, ideal_kernel);
  return result;
}


Mat butterworth_low_kernel(Mat src,double sigma, int n)
{
  Mat butterworth_low_pass(src.size(), CV_64FC1); 
  double D0 = sigma;
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
      butterworth_low_pass.at<double>(i, j) = 1.0 / (1 + pow(d / D0, 2 * n));
    }
  }

  String name = cv::format("BLPF d0=%.1f, n=%d", sigma, n);
  imshow(name, butterworth_low_pass);
  return butterworth_low_pass;
}

//Butterworth low pass filter
Mat lab::butterworth_low_paass_filter(Mat src, double d0, int n)
{
  Mat butterworth_kernel=butterworth_low_kernel(src, d0, n);
  Mat result = frequency_filter(src, butterworth_kernel);
  return result;
}

Mat gaussian_low_pass_kernel(Mat src,double sigma)
{
  Mat gaussianBlur(src.size(), CV_64FC1); 
  double d0 = 2 * sigma * sigma;
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols ; ++j) {
      double d = pow(double(i - src.rows / 2), 2)+pow(double(j - src.cols / 2), 2);
      gaussianBlur.at<double>(i, j) = exp(-d / d0);
    }
  }

  imshow("Gaussian low-pass filter", gaussianBlur);
  return gaussianBlur;
}

//Gauss low pass
Mat lab::gaussian_low_pass_filter(Mat src, double d0)
{
  Mat gaussian_kernel = gaussian_low_pass_kernel(src, d0);
  Mat result = frequency_filter(src, gaussian_kernel);
  return result;
}