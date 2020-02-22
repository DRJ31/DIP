#include "enlarge.hpp"
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

namespace lab
{
  int map(int num, double times)
  {
    return int(round(num / times));
  }
}

void neighbour(Mat &src, Mat &dst, double times)
{
  int rows = int(round(src.rows * times)), cols = int(round(src.cols * times));
  dst = Mat(rows, cols, src.type());
  uchar *ptr1, *ptr2;

  for (int i = 0; i < rows; ++i)
  {
    ptr1 = src.ptr<uchar>(lab::map(i, times));
    ptr2 = dst.ptr<uchar>(i);
    for (int j = 0; j < cols; ++j)
    {
      for (int k = 0; k < 3; ++k)
      {
        ptr2[j * 3 + k] = ptr1[lab::map(j, times) * 3 + k];
      }
    }
  }
}

// Main logic of pixel
void lab::NearestNeighbour(vector<cv::String> filenames)
{
  Mat srcImg, outImg;
  double times;
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
    neighbour(srcImg, outImg, times);
    imshow(filename, outImg);
  }
}