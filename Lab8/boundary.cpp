#include "func.hpp"
#include <iostream>

using namespace cv;
using namespace std;

bool is_boundary(Mat src, int x, int y)
{
  bool result = false;
  if ((int)src.at<uchar>(x, y) != 0) {
    result = result || lab::checkBorder(src, x, y, CHECK_X, CHECK_LESS);
    result = result || lab::checkBorder(src, x, y, CHECK_X, CHECK_MORE);
    result = result || lab::checkBorder(src, x, y, CHECK_Y, CHECK_LESS);
    result = result || lab::checkBorder(src, x, y, CHECK_Y, CHECK_MORE);
  }
  return result;
}

void paint_boundary(Mat &dst, int x, int y, cv::Size ksize)
{
  int rowStart, colStart, rowEnd, colEnd;
  rowStart = x - ksize.height;
  rowStart = rowStart > 0 ? rowStart : 0;
  colStart = y - ksize.width;
  colStart = colStart > 0 ? colStart : 0;
  rowEnd = ksize.height % 2 == 0 ? x + ksize.height : x + ksize.height + 1;
  rowEnd = rowEnd > dst.rows ? dst.rows : rowEnd;
  colEnd = ksize.width % 2 == 0 ? y + ksize.width : y + ksize.width + 1;
  colEnd = colEnd > dst.cols ? dst.rows : colEnd;

  for (int i = rowStart; i < rowEnd; ++i) {
    for (int j = colStart; j < colEnd; ++j) {
      dst.at<uchar>(i, j) = 255;
    }
  }
}

void convolution(Mat src, Mat &dst, cv::Size ksize)
{
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      if (is_boundary(src, i, j))
        paint_boundary(dst, i, j, ksize);
    }
  }
}

void lab::ExtractBoundaries()
{
  Mat src1 = imread("img/licoln.pgm", 0);
  Mat src2 = imread("img/U.pgm", 0);
  Mat dst1 = Mat(src1.size(), src1.type());
  Mat dst2 = Mat(src2.size(), src2.type());

  // Show original image
  imshow("licoln.jpg", src1);
  imshow("U.jpg", src2);

  // Paint borders
  convolution(src1, dst1, Size(3, 3));
  convolution(src2, dst2, Size(3, 3));

  imshow("licoln_boundary.jpg", dst1);
  imshow("U_boundary.jpg", dst2);
}