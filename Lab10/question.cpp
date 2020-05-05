#include "func.hpp"

using namespace cv;
using namespace std;

void Question1()
{
  Mat src = imread("img/large_septagon_gaussian_noise_mean_0_std_50_added.pgm", 0);
  Mat dst;

  imshow("lsgnm.jpg", src);

  vector<int> hist = getHist(src);
  uchar thres = otsu_threshold(hist, src);
  lab::threshold(src, dst, thres);
  imshow("OtsuOrigin.jpg", dst);

  medianBlur(src, dst, 5);
  hist = getHist(dst);
  thres = otsu_threshold(hist, dst);
  lab::threshold(dst, dst, thres);
  imshow("OtsuMedian.jpg", dst);
}