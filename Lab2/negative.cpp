#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void negative_image(Mat src, Mat &dst)
{
  int rows = src.rows, cols = src.cols;
  dst = Mat(rows, cols, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      dst.at<Vec3b>(i, j) = Vec3b(255, 255, 255) - src.at<Vec3b>(i, j);
    }
  }
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