#include <iostream>
#include <cmath>
#include "omp.h"
#include "func.hpp"

#define PI 3.1415926535

using namespace std;
using namespace cv;



void lab::magnitude(Mat src1, Mat src2, Mat &dst)
{
  int height = src1.rows, width = src2.cols;
  dst = Mat(src1.size(), src1.type());

  #pragma omp parallel for
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      dst.at<double>(i, j) = sqrt(pow(src1.at<double>(i, j), 2) + pow(src2.at<double>(i, j), 2));
    }
  }
}

void lab::log(Mat src, Mat &dst)
{
  int height = src.rows, width = src.cols;
  dst = Mat(src.size(), src.type());

  #pragma omp parallel for
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      dst.at<double>(i, j) = std::log(src.at<double>(i, j));
    }
  }
}

void lab::normalize(Mat src, Mat &dst) 
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

void lab::norm_angle(Mat src, Mat &dst)
{
  int height = src.rows, width = src.cols;

  #pragma omp parallel for
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      dst.at<double>(i, j) = src.at<double>(i, j) / sqrt(2);
    }
  }
}

void lab::shift(Mat src, Mat &dst)
{
  dst = src;

  // Ensure size of image is even
	dst = dst(cv::Rect(0, 0, dst.cols & -2, dst.rows & -2));
 
	// Rearrange points to ensure origin point is in the middle
	int cx = dst.cols / 2;
	int cy = dst.rows / 2;
	Mat q0(dst(cv::Rect(0, 0, cx, cy)));
	Mat q1(dst(cv::Rect(cx, 0, cx, cy)));
	Mat q2(dst(cv::Rect(0, cy, cx, cy)));
	Mat q3(dst(cv::Rect(cy, cy, cx, cy)));
 
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void lab::phase(Mat src1, Mat src2, Mat &dst)
{
  int height = src1.rows, width = src1.cols;
  dst = Mat(src1.size(), src1.type());

  #pragma omp parallel for
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      dst.at<double>(i, j) = atan2(src2.at<double>(i, j), src1.at<double>(i, j)) * 180 / PI;
    }
  }
}


void lab::dft(Mat src, Mat &dst1, Mat &dst2) 
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

void lab::idft(Mat src, Mat &dst1, Mat &dst2) 
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
          dst1.at<double>(u, v) += src.at<double>(x, y) * cos(powerX + powerY) / (height * width);
          dst2.at<double>(u, v) += src.at<double>(x, y) * sin(powerX + powerY) / (height * width);
        }
      }
    }
  }
}