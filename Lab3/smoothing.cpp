#include <iostream>
#include <algorithm>
#include "func.hpp"

using namespace std;
using namespace cv;

void binarization(Mat src, Mat &dst)
{
  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      for (int m = 0; m < 3; ++m)
      {
        dst.at<Vec3b>(i, j)[m] = src.at<Vec3b>(i, j)[m] > 255 / 2 ? 255 : 0;
      }
    }
  }
}

void operation(int selected, Mat src, Mat &dst1, Mat &dst2)
{
  switch (selected)
  {
  case 1:
    /* code */
    break;
  case 2:
    break;
  case 3:
    binarization(src, dst1);
    break;
  default:
    break;
  }
}

void lab::Smoothing(cv::String filename)
{
  int selected;
  Mat src, dst1, dst2;
  src = imread(filename);
  dst1 = Mat(src.rows, src.cols, src.type());
  dst2 = Mat(src.rows, src.cols, src.type());

  while (true)
  {
    cout << "Select a smoothing filter: " << endl;
    cout << "1. Averaging Filter" << endl;
    cout << "2. Median Filter" << endl;
    cout << "3. Binarization Filter" << endl;
    cout << "Your selection: ";
    cin >> selected;
    if (selected > 0 && selected < 4) break;
  }

  operation(selected, src, dst1, dst2);
  imshow("Original Image", src);
  if (selected == 3)
  {
    imshow("Binarization Filter", dst1);
  }
  else
  {
    imshow("3x3 Filter", dst1);
    imshow("5x5 Filter", dst2);
  }

  waitKey(0);
}