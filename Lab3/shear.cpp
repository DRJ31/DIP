#include <iostream>
#include <cmath>
#include <algorithm>
#include "func.hpp"

using namespace std;
using namespace cv;

int max_size(Mat src, double ssize, int stype)
{
  int msize = max(src.rows, src.cols);
  switch (stype)
  {
  case 1:
    msize = max(src.rows, int(ssize * src.rows + src.cols));
    break;
  case 2:
    msize = max(src.cols, int(ssize * src.cols + src.rows));
  default:
    break;
  }
  return msize;
}

void shear(int &x, int &y, double ssize, int msize, int stype)
{
  int u = x - msize / 2, v = y - msize / 2;
  if (stype == 1)
    x = u + int(ssize * v) + msize / 2;
  else if (stype == 2)
    y = v + int(ssize * u) + msize / 2;
}

void paint(Mat src, Mat &dst1, Mat &dst2, double ssize, int msize, int stype)
{
  int spanX = (msize - src.rows) / 2, spanY = (msize - src.cols) / 2;

  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      int m = i + spanX, n = j + spanY;
      dst1.at<Vec3b>(m, n) = src.at<Vec3b>(i, j);
      shear(m, n, ssize, msize, stype);
      dst2.at<Vec3b>(m, n) = src.at<Vec3b>(i, j);
    }
  }
}

void lab::Shear(cv::String filename)
{
  int stype, msize;
  double ssize;
  Mat src, dst1, dst2;
  src = imread(filename);

  while (true)
  {
    cout << "Please choose a shear type: " << endl;
    cout << "1. Vertical" << endl;
    cout << "2. Horizontal" << endl;
    cout << "Your selection: ";
    cin >> stype;
    if (stype == 1 || stype == 2) break;
  }
  
  cout << "Please input shear size: ";
  cin >> ssize;
  msize = max_size(src, ssize, stype);
  dst1 = Mat(msize, msize, src.type());
  dst2 = Mat(msize, msize, src.type());

  paint(src, dst1, dst2, ssize, msize, stype);
  imshow("Original Image", dst1);
  imshow("Sheared Image", dst2);

  waitKey(0);
}