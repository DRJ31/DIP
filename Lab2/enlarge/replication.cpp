#include "enlarge.hpp"
#include <vector>

using namespace cv;
using namespace std;

// pixel (uchar*) -> Pointer of row of original image
// row (int) -> Index of current row
// cols (int) -> Number of columns of original image
// times (int) -> Times of image enlargement
void setPoint(Mat src, Mat &dst, int index, int row, int cols, int times)
{
  for (int j = 0; j < cols; ++j)
  {
    for (int n = 0; n < times; ++n) 
    {
      dst.at<Vec3b>(row, j * times + n) = src.at<Vec3b>(index, j);
    }
  }
}

// Main algorithm of pixel replication
void replication(Mat src, Mat &dst, int times)
{
  int rows = src.rows, cols = src.cols;
  dst = Mat(rows * times, cols * times, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int m = 0; m < times; ++m)
    {
      setPoint(src, dst, i, i * times + m, cols, times);
    }
  }
}

// Main logic of pixel
void lab::PixelReplication(vector<cv::String> filenames)
{
  Mat srcImg, outImg;
  int times;
  cout << "Input magnification you want to expand: ";
  cin >> times;
  if (times < 1)
  {
    cout << "Magnification should be larger than 1." << endl;
    return;
  }

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    replication(srcImg, outImg, times);
    imshow(filename, outImg);
  }
}