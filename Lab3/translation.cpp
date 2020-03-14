#include <iostream>
#include <cmath>
#include "func.hpp"

using namespace std;
using namespace cv;

void paint(Mat src, Mat &dst, int vertical, int horizontal)
{
  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      dst.at<Vec3b>(i + vertical, j + horizontal) = src.at<Vec3b>(i, j);
    }
  }
}

void lab::Translation(cv::String filename)
{
  int vertical, horizontal, x1, x2, y1, y2;
  Mat src, dst1, dst2;
  src = imread(filename);

  cout << "Input vertical pixels you want to translate: ";
  cin >> vertical;
  cout << "Input horizontal pixels you want to translate: ";
  cin >> horizontal;

  dst1 = Mat(src.rows + abs(vertical), src.cols + abs(horizontal), src.type());
  dst2 = Mat(src.rows + abs(vertical), src.cols + abs(horizontal), src.type());

  if (vertical < 0) 
  {
    x1 = abs(vertical);
    x2 = 0;
  } 
  else
  {
    x1 = 0;
    x2 = vertical;
  }

  if (horizontal < 0) 
  {
    y1 = abs(horizontal);
    y2 = 0;
  } 
  else
  {
    y1 = 0;
    y2 = horizontal;
  }

  paint(src, dst1, x1, y1);
  paint(src, dst2, x2, y2);

  imshow("Original Position", dst1);
  imshow("Translated Position", dst2);

  waitKey(0);
}