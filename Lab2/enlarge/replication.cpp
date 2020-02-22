#include "enlarge.hpp"
#include <vector>

using namespace cv;
using namespace std;

// pixel (uchar*) -> Pointer of row of original image
// row (int) -> Index of current row
// cols (int) -> Number of columns of original image
// times (int) -> Times of image enlargement
void setPoint(Mat &img, uchar *pixel, int row, int cols, int times)
{
  uchar* ptr = img.ptr<uchar>(row);

  for (int j = 0; j < cols * 3; ++j)
  {
    for (int n = 0; n < times; ++n) 
    {
      ptr[j * times + n] = pixel[j];
    }
  }
}

// Main algorithm of pixel replication
void replication(Mat &src, Mat &dst, int times)
{
  int rows = src.rows, cols = src.cols;
  dst = Mat(rows * times, cols * times, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int m = 0; m < times; ++m)
    {
      setPoint(dst, src.ptr<uchar>(i), i * times + m, cols, times);
    }
  }
}

// Main logic of pixel
void lab::PixelReplication(vector<cv::String> filenames)
{
  Mat srcImg, outImg;

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    replication(srcImg, outImg, 2);
    imshow(filename, outImg);
  }
}