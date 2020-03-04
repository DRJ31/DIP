#include <iostream>
#include <cmath>
#include <algorithm>
#include "func.hpp"

#define PI 3.1415926535

using namespace std;
using namespace cv;

void rotate(int &x, int &y, int degree, Mat src)
{
  int centerX = int(round(src.rows * 1.5 / 2)), centerY = int(round(src.cols * 1.5 / 2));
  int u = x - centerX, v = y - centerY;
  y = int(round(v * cos(degree * PI / 180) - u * sin(degree * PI / 180))) + centerY;
  x = int(round(u * cos(degree * PI / 180) + v * sin(degree * PI / 180))) + centerX;
}

void paint(Mat src, Mat &dst1, Mat &dst2, int degree)
{
  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      int m = i + src.rows / 4, n = j + src.cols / 4;
      dst1.at<Vec3b>(m, n) = src.at<Vec3b>(i, j);
      rotate(m, n, degree, src);
      dst2.at<Vec3b>(m, n) = src.at<Vec3b>(i, j);
    }
  }
}

void lab::Rotation(cv::String filename)
{
  int degree, mat_size;
  Mat src, dst1, dst2;
  src = imread(filename);
  mat_size = int(round(std::max(src.rows, src.cols) * 1.5));
  dst1 = Mat(mat_size, mat_size, src.type());
  dst2 = Mat(mat_size, mat_size, src.type());

  while (true)
  {
    cout << "Input degree you want to rotate: ";
    cin >> degree;
    if (degree < 360 && degree > -360) break;
    cout << "The degree shoule be more than -360 and less than 360!" << endl;
  }

  paint(src, dst1, dst2, degree);
  imshow("Original Image", dst1);
  imshow("Rotated Image", dst2);

  waitKey(0);
}