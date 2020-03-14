#include <iostream>
#include <algorithm>
#include <vector>
#include "func.hpp"

using namespace std;
using namespace cv;

Mat create_tmp(Mat src, Size ksize)
{
  int offsetX = ksize.height / 2, offsetY = ksize.width / 2;
  Mat tmp = Mat(src.rows + offsetX * 2, src.cols + offsetY * 2, src.type());

  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      if (i < offsetX || j < offsetY || i > src.rows - offsetX || j > src.cols - offsetY)
        tmp.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
      tmp.at<Vec3b>(i + offsetX, j + offsetY) = src.at<Vec3b>(i, j);
    }
  }

  return tmp;
}

bool median_compare(Vec3b a, Vec3b b)
{
  return a[0] + a[1] + a[2] < b[0] + b[1] + b[2];
}

Vec3b median(int x, int y, Mat tmp, Size ksize)
{
  vector<Vec3b> points(ksize.height * ksize.width);

  for (int i = x; i < x + ksize.height; ++i)
  {
    for (int j = y; j < y + ksize.width; ++j)
    {
      for (int m = 0; m < 3; ++m)
      {
        points.push_back(tmp.at<Vec3b>(i, j));
      }
    }
  }

  sort(points.begin(), points.end(), median_compare);
  return points[points.size() / 2];
}

Vec3b averaging(int x, int y, Mat tmp, Size ksize)
{
  vector<int> sum(3);

  for (int i = x; i < x + ksize.height; ++i)
  {
    for (int j = y; j < y + ksize.width; ++j)
    {
      for (int m = 0; m < 3; ++m)
      {
        sum[m] += tmp.at<Vec3b>(i, j)[m];
      }
    }
  }

  for (int i = 0; i < 3; ++i)
  {
    sum[i] /= ksize.height * ksize.width;
  }
  return Vec3b(sum[0], sum[1], sum[2]);
}

void convolution(Mat src, Mat &dst, Size ksize, Vec3b (*filter)(int, int, Mat, Size))
{
  Mat tmp;
  tmp = create_tmp(src, ksize);

  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      dst.at<Vec3b>(i, j) = filter(i, j, tmp, ksize);
    }
  }
}

void binarization(Mat src, Mat &dst)
{
  for (int i = 0; i < src.rows; ++i)
  {
    for (int j = 0; j < src.cols; ++j)
    {
      uchar c = src.at<Vec3b>(i, j)[0] > 255 / 2 ? 255 : 0;
      dst.at<Vec3b>(i, j) = Vec3b(c, c, c);
    }
  }
}

void operation(int selected, Mat src, Mat &dst1, Mat &dst2)
{
  switch (selected)
  {
  case 1:
    convolution(src, dst1, Size(3, 3), averaging);
    convolution(src, dst2, Size(5, 5), averaging);
    break;
  case 2:
    convolution(src, dst1, Size(3, 3), median);
    convolution(src, dst2, Size(5, 5), median);
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