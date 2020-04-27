#include "func.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void lab::SeperateImage()
{
  Mat src = imread("img/bubbles_on_black_background.pgm", 0);
  Mat dst1, dst2, dst3;
}