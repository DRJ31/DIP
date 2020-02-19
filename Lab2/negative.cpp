#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void negative(cv::String filename) 
{
  Mat srcImg = imread(filename);
  Mat outImg;

  bitwise_not(srcImg, outImg);
  imshow(filename, outImg);
}

int main()
{
  vector<cv::String> filenames;
  cv::String pattern = "img/*.pgm";

  glob(pattern, filenames);

  for (size_t i = 0; i < filenames.size(); ++i) 
  {
    negative(filenames[i]);
  }

  waitKey(0);
  return 0;
}