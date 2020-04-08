#include <opencv2/opencv.hpp>

namespace lab
{
  void magnitude(cv::Mat src1, cv::Mat src2, cv::Mat &dst);

  void log(cv::Mat src, cv::Mat &dst);

  void normalize(cv::Mat src, cv::Mat &dst) ;

  void dft(cv::Mat src, cv::Mat &dst1, cv::Mat &dst2);

  void idft(cv::Mat src, cv::Mat &dst1, cv::Mat &dst2);

  void shift(cv::Mat src, cv::Mat &dst);

  void phase(cv::Mat src1, cv::Mat src2, cv::Mat &dst);

  void norm_angle(cv::Mat src, cv::Mat &dst);

  cv::Mat gaussian_low_pass_filter(cv::Mat src, double d0);

  cv::Mat butterworth_low_paass_filter(cv::Mat src, double d0, int n);

  cv::Mat ideal_low_pass_filter(cv::Mat src, double sigma);

  void one_amptitude(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
}