#include "enlarge.hpp"
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

namespace lab
{
  typedef struct Point {
    double row;
    double col;
    Vec3b color;
  } Point;

  void bilinear(Mat src, Mat &dst, double times);

  void linear(Point &p, Point p1, Point p2);
}


void lab::linear(lab::Point &p, lab::Point p1, lab::Point p2)
{
  if (p1.row == p2.row) 
  {
    for (int i = 0; i < 3; ++i)
    {
      p.color[i] = round((p2.col - p.col) * 1.0 / (p2.col - p1.col) * p1.color[i] 
      + (p.col - p1.col) * 1.0 / (p2.col - p1.col) * p2.color[i]);
    }
  }
  else
  {
    for (int i = 0; i < 3; ++i)
    {
      p.color[i] = round((p2.row - p.row) * 1.0 / (p2.row - p1.row) * p1.color[i] 
      + (p.row - p1.row) * 1.0 / (p2.row - p1.row) * p2.color[i]);
    }
  }
}

void lab::bilinear(Mat src, Mat &dst, double times)
{
  int rows = int(round(src.rows * times)), cols = int(round(src.cols * times));
  dst = Mat(rows, cols, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      double mapX = i * 1.0 / rows * src.rows, mapY = j * 1.0 / cols * src.cols;
      double x1 = floor(mapX), x2 = ceil(mapX), y1 = floor(mapY), y2 = ceil(mapY);
      lab::Point p11 = {x1, y1, src.at<Vec3b>(x1, y1)};
      lab::Point p12 = {x1, y2, src.at<Vec3b>(x1, y2)};
      lab::Point p21 = {x2, y1, src.at<Vec3b>(x2, y1)};
      lab::Point p22 = {x2, y2, src.at<Vec3b>(x2, y2)};
      lab::Point px1 = {mapX, y1, Vec3b()}, px2 = {mapX, y2, Vec3b()}, p = {mapX, mapY, Vec3b()};
      lab::linear(px1, p11, p21);
      lab::linear(px2, p12, p22);
      lab::linear(p, px1, px2);
      dst.at<Vec3b>(i, j) = p.color;
    }
  }
}


void lab::BilinearInterpolation(vector<cv::String> filenames)
{
  Mat srcImg, outImg;
  double times;
  cout << "Input magnification you want to expand: ";
  cin >> times;
  if (times < 1)
  {
    cout << "Magnification should be larger than 1." << endl;
    return;
  }

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    lab::bilinear(srcImg, outImg, times);
    imshow(filename, outImg);
  }
}