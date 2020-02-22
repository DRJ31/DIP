#include "reduction.hpp"
#include <vector>

using namespace std;
using namespace cv;

void alternative(Mat src, Mat &dst)
{
  int rows = src.rows / 2, cols = src.cols / 2;
  dst = Mat(rows, cols, src.type());
  uchar *ptr1, *ptr2;

  for (int i = 0; i < rows; ++i)
  {
    ptr1 = src.ptr<uchar>(i * 2);
    ptr2 = dst.ptr<uchar>(i);
    for (int j = 0; j < cols; ++j)
    {
      for (int k = 0; k < 3; ++k)
      {
        *ptr2 = ptr1[j * 3 * 2 + k];
        ptr2++;
      }
    }
  }
}

void lab::AlternativeLine(vector<cv::String> filenames)
{
  Mat srcImg, outImg;

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    alternative(srcImg, outImg);
    imshow(filename, outImg);
  }
}