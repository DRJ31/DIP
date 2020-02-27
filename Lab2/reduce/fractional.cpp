#include "reduction.hpp"
#include "../enlarge/enlarge.hpp"
#include <vector>

using namespace std;
using namespace cv;


void lab::FractionalLinearReduction(vector<cv::String> filenames)
{
  Mat srcImg, outImg;
  double ratio;
  cout << "Input ratio you want to reduce (0-1): ";
  cin >> ratio;
  if (ratio >= 1)
  {
    cout << "Ratio should be 0-1." << endl;
    return;
  }

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    lab::Bilinear(srcImg, outImg, ratio);
    imshow(filename, outImg);
  }
}