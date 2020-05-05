#include <vector>
#include <opencv2/opencv.hpp>


namespace lab
{
  void threshold(cv::Mat src, cv::Mat &dst, uchar thres);
}

std::vector<int> getHist(cv::Mat src);
uchar otsu_threshold(std::vector<int> histogram, cv::Mat src);

void Question1();
void Question2();
void Question3();
