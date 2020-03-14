#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "func.hpp"

using namespace std;
using namespace cv;


void gamma(Mat src, Mat &dst, double gval)
{
  vector<uchar> lut(256);

  for (int i = 0; i < 256; ++i) {
    lut[i] = round(pow(i / 255.0, gval) * 255);
  }

  for (int i = 0; i < src.size().height; ++i) {
    for (int j = 0; j < src.size().width; ++j) {
      for (int m = 0; m < 3; ++m) {
        dst.at<Vec3b>(i, j)[m] = lut[src.at<Vec3b>(i, j)[m]];
      }
    }
  }
}


void lab::Gamma(cv::String filename)
{
  Mat src = imread(filename);
  vector<double> gval = {0.1, 0.4, 0.6, 0.8, 1};
  vector<Mat> dst(5);

  for (int i = 0; i < 5; ++i) {
    ostringstream os;
    os << "Gamma Value: " << gval[i];
    dst[i] = Mat(src.size(), src.type());
    gamma(src, dst[i], gval[i]);
    imshow(os.str(), dst[i]);
  }

  waitKey(0);
}