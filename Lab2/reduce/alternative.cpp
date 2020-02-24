#include "reduction.hpp"
#include <vector>

using namespace std;
using namespace cv;

void alternative(Mat src, Mat &dst)
{
  int rows = src.rows / 2, cols = src.cols / 2;
  dst = Mat(rows, cols, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      dst.at<Vec3b>(i, j) = src.at<Vec3b>(i * 2, j * 2);
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