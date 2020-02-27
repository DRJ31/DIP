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

void neighbour(Mat src, Mat &dst, double times)
{
  int rows = int(round(src.rows * times)), cols = int(round(src.cols * times));
  dst = Mat(rows, cols, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      dst.at<Vec3b>(i, j) = src.at<Vec3b>(lab::map(i, times), lab::map(j, times));
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
    imwrite("nearest_neighbour_" + filename.substr(4, filename.length() - 8) + ".jpg", outImg);
    imshow(filename, outImg);
  }
}