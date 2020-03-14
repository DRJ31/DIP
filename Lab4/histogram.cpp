#include <iostream>
#include <map>
#include <cmath>
#include "func.hpp"

using namespace std;
using namespace cv;


map<uchar, int> cdfTable(Mat src, int &cdf_min, Size size)
{
  map<uchar, int> table;
  int previous = 0;

  for (int i = 0; i < size.height; ++i) {
    for (int j = 0; j < size.width; ++j) {
      uchar greyScale = src.at<uchar>(i, j);
      if (!table[greyScale])
        table[greyScale] = 1;
      else
        table[greyScale] += 1;
    }
  }


  for (map<uchar, int>::iterator it = table.begin(); it != table.end(); ++it) {
    it->second += previous;
    previous = it->second;
  }

  cdf_min = table.begin() -> second;
  return table;
}


void histogram(Mat src, Mat &dst)
{
  int cdf_min;
  Size size = src.size();
  map<uchar, int> cdf_table = cdfTable(src, cdf_min, size);

  for (map<uchar, int>::iterator it = cdf_table.begin(); it != cdf_table.end(); ++it) {
    it->second = round((it->second - cdf_min) * 1.0 / (size.width * size.height - cdf_min) * 255);
  }

  for (int i = 0; i < size.height; ++i) {
    for (int j = 0; j < size.width; ++j) {
      dst.at<uchar>(i, j) = cdf_table[src.at<uchar>(i, j)];
    }
  }
}


void lab::Histogram(cv::String filename)
{
  Mat src, dst;
  src = imread(filename, 0);
  dst = Mat(src.size(), src.type());

  histogram(src, dst);
  imshow("Histogram", dst);
  waitKey(0);
}