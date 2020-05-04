#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
  Mat src = imread("rect.png", 0);
  Mat kernel = imread("kernel.png", 0);
  Mat C, D, E, F;
  erode(src, C, kernel);
  dilate(C, D, kernel);
  erode(D, E, kernel);
  dilate(E, F, kernel);
  imwrite("rectc.jpg", C);
  imwrite("rectd.jpg", D);
  imwrite("recte.jpg", E);
  imwrite("rectf.jpg", F);
  waitKey(0);
  return 0;
}