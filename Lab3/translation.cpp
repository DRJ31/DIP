#include <iostream>
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
  int vertical, horizontal;
  Mat src, dst1, dst2;
  src = imread(filename);

  cout << "Input vertical pixels you want to translate: ";
  cin >> vertical;
  cout << "Input horizontal pixels you want to translate: ";
  cin >> horizontal;

  dst1 = Mat(src.rows + vertical, src.cols + horizontal, src.type());
  dst2 = Mat(src.rows + vertical, src.cols + horizontal, src.type());

  paint(src, dst1, 0, 0);
  paint(src, dst2, vertical, horizontal);

  imshow("Original Position", dst1);
  imshow("Translated Position", dst2);

  waitKey(0);
}