#include <vector>
#include <opencv2/opencv.hpp>


namespace lab
{
  void threshold(cv::Mat src, cv::Mat &dst, uchar thres);
}

typedef struct seedPoint {
  int x, y;
} SeedPoint;

std::vector<int> getHist(cv::Mat src);
uchar otsu_threshold(std::vector<int> histogram, cv::Mat src);
void movingAvg(cv::Mat src, cv::Mat &dst, int steps, double b);
void regionGrow(cv::Mat src, cv::Mat &dst, SeedPoint pt, int thres);

void Question1();
void Question2();
void Question3();
void Question4();
