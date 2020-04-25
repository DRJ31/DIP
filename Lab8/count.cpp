#include <fstream>
#include "func.hpp"

using namespace cv;
using namespace std;

bool check_position(Mat src, int x, int y)
{
  return x > 0 && y > 0 && x < src.rows - 1 && y < src.cols - 1;
}

bool is_start_point(Mat src, int x, int y)
{
  bool result = false;
  if ((int)src.at<uchar>(x, y) != 0 && check_position(src, x, y)) {
    result = true;
    result = result && lab::checkBorder(src, x, y, CHECK_X, CHECK_LESS);
    result = result && lab::checkBorder(src, x, y, CHECK_Y, CHECK_LESS);
  }
  return result;
}

bool is_row_end_point(Mat src, int x, int y)
{
  bool result = false;
  if ((int)src.at<uchar>(x, y) != 0 && check_position(src, x, y)) {
    result = true;
    result = result && lab::checkBorder(src, x, y, CHECK_X, CHECK_MORE);
    result = result && lab::checkBorder(src, x, y, CHECK_Y, CHECK_LESS);
  }
  return result;
}

bool is_col_end_point(Mat src, int x, int y)
{
  bool result = false;
  if ((int)src.at<uchar>(x, y) != 0) {
    result = true;
    result = result && lab::checkBorder(src, x, y, CHECK_X, CHECK_LESS);
    result = result && lab::checkBorder(src, x, y, CHECK_Y, CHECK_MORE);
  }
  return result;
}

int count_points(Mat src, int x, int y) 
{
  int rows = 1, cols = 1;

  for (int i = x; i < src.rows; ++i) {
    if (is_row_end_point(src, i, y)) {
      rows = i - x + 1;
      break;
    }
  }

  for (int i = y; i < src.cols; ++i) {
    if (is_col_end_point(src, x, i)) {
      cols = i - y + 1;
      break;
    }
  }

  return rows * cols;
}

void lab::CountPixels() 
{
  Mat src = imread("img/connected.pgm", 0);
  int height = src.rows, width = src.cols, count;
  ofstream outfile;
  outfile.open("points.txt");
  
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (is_start_point(src, i, j)) {
        outfile << "Point(" << i << ", " << j << "): ";
        count = count_points(src, i, j);
        outfile << count << endl;
      }
    }
  }

  outfile.close();
}