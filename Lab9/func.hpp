#include <vector>
#include <opencv2/opencv.hpp>

#define PI 3.1415926535

namespace lab
{
  // Convolution functions
  void convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, uchar (*filter)(int, int, cv::Mat, cv::Size));
  void convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, double sigma, uchar (*filter)(int, int, cv::Mat, cv::Size, double));
  void convolution(cv::Mat src, cv::Mat &d, cv::Mat &dx, cv::Mat &dy, cv::Size ksize, int filterType, std::vector<uchar> (*filter)(int, int, cv::Mat, cv::Size, int));
  void convolution(cv::Mat d, cv::Mat dx, cv::Mat dy, cv::Mat &dst, uchar (*filter)(int, int, cv::Mat, cv::Mat, cv::Mat));

  // Threshold
  void threshold(cv::Mat src, cv::Mat &dst, double thres);
}


// Main functions of each part
void Question1();
void Question2();
void Question3();