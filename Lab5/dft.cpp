#include <iostream>
#include <cmath>
#include "omp.h"
#include "func.hpp"

#define PI 3.1415926535

using namespace std;
using namespace cv;


namespace lab
{
  void magnitude(Mat src1, Mat src2, Mat &dst)
  {
    int height = src1.rows, width = src2.cols;

    #pragma omp parallel for
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        dst.at<double>(i, j) = sqrt(pow(src1.at<double>(i, j), 2) + pow(src2.at<double>(i, j), 2));
      }
    }
  }

  void log(Mat src, Mat &dst)
  {
    int height = src.rows, width = src.cols;

    #pragma omp parallel for
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        dst.at<double>(i, j) = std::log(src.at<double>(i, j));
      }
    }
  }

  void normalize(Mat src, Mat &dst) 
  {
    double min = src.at<double>(0, 0), max = src.at<double>(0, 0);
    dst = Mat(src.size(), CV_8UC1);

    for (int i = 0; i < src.rows; ++i) {
      for (int j = 0; j < src.cols; ++j) {
        if (src.at<double>(i, j) < min)
          min = src.at<double>(i, j);
        if (src.at<double>(i, j) > max)
          max = src.at<double>(i, j);
      }
    }

    #pragma omp parallel for
    for (int i = 0; i < src.rows; ++i) {
      for (int j = 0; j < src.cols; ++j) {
        dst.at<uchar>(i, j) = round((src.at<double>(i, j) - min) / (max - min) * 255);
      }
    }
  }
}


void dft2(Mat src, Mat &dst1, Mat &dst2) 
{
  int height = src.rows, width = src.cols;
  dst1 = Mat(src.size(), CV_64FC1);
  dst2 = Mat(src.size(), CV_64FC1);

  double fixedFactorX = (-2 * PI) / height;
  double fixedFactorY = (-2 * PI) / width;

  #pragma omp parallel for
  for (int u = 0; u < src.rows; ++u) {
    cout << "u: " << u << endl;
    for (int v = 0; v < src.cols; ++v) {
      dst1.at<double>(u, v) = 0.0;
      dst2.at<double>(u, v) = 0.0;
      for (int x = 0; x < src.rows; ++x) {
        for (int y = 0; y < src.cols; ++y) {
          double powerX = u * x * fixedFactorX;
          double powerY = v * y * fixedFactorY;
          dst1.at<double>(u, v) += src.at<uchar>(x, y) * cos(powerX + powerY);
          dst2.at<double>(u, v) += src.at<uchar>(x, y) * sin(powerX + powerY);
        }
      }
    }
  }
}


void lab::DFT(cv::String filename)
{
  Mat src = imread(filename, 0);
  Mat dst1, dst2;

  dft2(src, dst1, dst2);
  lab::magnitude(dst1, dst2, dst1);
  dst1 += 1;
  lab::log(dst1, dst1);

  // Ensure size of image is even
	dst1 = dst1(cv::Rect(0, 0, dst1.cols & -2, dst1.rows & -2));
 
	// Rearrange points to ensure origin point is in the middle
	int cx = dst1.cols / 2;
	int cy = dst1.rows / 2;
	Mat q0(dst1(cv::Rect(0, 0, cx, cy)));
	Mat q1(dst1(cv::Rect(cx, 0, cx, cy)));
	Mat q2(dst1(cv::Rect(0, cy, cx, cy)));
	Mat q3(dst1(cv::Rect(cy, cy, cx, cy)));
 
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

  // Normalize points to show image on imshow
  lab::normalize(dst1, dst1);


  imshow("Pic", dst1);
  imwrite("pic.jpg", dst1);
}