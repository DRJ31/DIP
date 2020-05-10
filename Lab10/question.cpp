#include "func.hpp"
#include <iostream>

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

void Question2()
{
  // Divide original image into 2x3 parts
  Mat src = imread("img/septagon_noisy_shaded.pgm", 0);
  Mat dst = Mat(src.size(), src.type());
  Mat tmp = Mat(src.rows / 2, src.cols / 3, src.type());
  vector<int> hist;
  uchar thres;

  imshow("septagon.jpg", src);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int m = i * src.rows / 2; m < (i + 1) * src.rows / 2; ++m) {
        for (int n = j * src.cols / 3; n < (j + 1) * src.cols / 3; ++n) {
          tmp.at<uchar>(m - i * src.rows / 2, n - j * src.cols / 3) = src.at<uchar>(m, n);
        }
      }
      hist = getHist(tmp);
      thres = otsu_threshold(hist, tmp);
      lab::threshold(tmp, tmp, thres);
      for (int m = i * src.rows / 2; m < (i + 1) * src.rows / 2; ++m) {
        for (int n = j * src.cols / 3; n < (j + 1) * src.cols / 3; ++n) {
          dst.at<uchar>(m, n) = tmp.at<uchar>(m - i * src.rows / 2, n - j * src.cols / 3);
        }
      }
      if (i == 1 && j == 2) {
        imshow("partition.jpg", dst);
        waitKey(0);
      }
    }
  }
}

void Question3()
{
  Mat src = imread("img/spot_shaded_text_image.pgm", 0);
  Mat dst;
  movingAvg(src, dst, 20, 0.5);
  imshow("text.jpg", src);
  imshow("movingAverage.jpg", dst);
}

void Question4()
{
  Mat src1 = imread("img/defective_weld.pgm", 0);
  Mat src2 = imread("img/noisy_region.pgm", 0);
  Mat dst1, dst2;
  SeedPoint pt1{ 251, 291 }, pt2{ 391, 369 };

  regionGrow(src1, dst1, pt1, 110);
  regionGrow(src2, dst2, pt2, 100);

  imshow("weld.jpg", src1);
  imshow("reigion.jpg", src2);
  imshow("grow_weld.jpg", dst1);
  imshow("grow_region.jpg", dst2);
}