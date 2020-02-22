#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void negative_image(Mat &src, Mat &dst)
{
  int rows = src.rows, cols = src.cols;
  uchar* ptr;

  for (int i = 0; i < rows; ++i)
  {
    ptr = src.ptr<uchar>(i);
    for (int j = 0; j < cols * 3; ++j)
    {
      ptr[j] = 255 - ptr[j];
    }
  }

  dst = src;
}

void negative(cv::String filename)
{
  Mat srcImg = imread(filename);
  Mat outImg;

  negative_image(srcImg, outImg);
  imshow(filename, outImg);
}

int main()
{
  vector<cv::String> filenames;
  cv::String pattern = "img/*.pgm";

  glob(pattern, filenames);

  for (auto filename : filenames)
  {
    negative(filename);
  }

  waitKey(0);
  return EXIT_SUCCESS;
}