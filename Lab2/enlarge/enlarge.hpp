#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

namespace lab 
{
  void PixelReplication(std::vector<cv::String> filenames);

  void NearestNeighbour(std::vector<cv::String> filenames);

  void BilinearInterpolation(std::vector<cv::String> filenames);
}