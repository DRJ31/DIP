#include <opencv2/opencv.hpp>


namespace lab
{
  void convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, uchar (*filter)(int, int, cv::Mat, cv::Size));
}

// Main functions of each part
void Question1();
void Question2();
void Question3();