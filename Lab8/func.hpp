#include <opencv2/opencv.hpp>

#define CHECK_X 0
#define CHECK_Y 1
#define CHECK_LESS 0
#define CHECK_MORE 1

namespace lab
{
  void CountPixels();

  void Morphs();

  void ExtractBoundaries();

  bool checkBorder(cv::Mat src, int x, int y, int xy, int lm);

  void SeperateImage();
}