#include <cmath>
#include <numeric>
#include "func.hpp"

using namespace cv;
using namespace std;


void globalThresholding(Mat src, Mat &dst, double t0, double init)
{
  vector<uchar> more, less;
  double t1 = init, t2 = 0;

  while (true) {
    for (int i = 0; i < src.rows; ++i) {
      for (int j = 0; j < src.cols; ++j) {
        uchar tmp = src.at<uchar>(i, j);
        tmp > t1 ? more.push_back(tmp) : less.push_back(tmp);
      }
    }
    t2 = (std::accumulate(more.begin(), more.end(), 0) / more.size() + std::accumulate(less.begin(), less.end(), 0) / less.size()) / 2;
    if (abs(t2 - t1) < t0)
      break;
    t1 = t2;
    more.clear();
    more.shrink_to_fit();
    less.clear();
    less.shrink_to_fit();
  }

  lab::threshold(src, dst, t2);
}


void Question3()
{
  Mat src1 = imread("img/polymersomes.pgm", 0);
  Mat src2 = imread("img/noisy_fingerprint.pgm", 0);
  Mat dst1, dst2;

  // Original image
  imshow("Poly.jpg", src1);
  imshow("Finger.jpg", src2);

  // Global Thresholding
  globalThresholding(src1, dst1, 0.5, 100);
  globalThresholding(src2, dst2, 0.5, 100);

  imshow("GTPoly.jpg", dst1);
  imshow("GTFinger.jpg", dst2);
}