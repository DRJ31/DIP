#include "func.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void lab::SeperateImage()
{
  Mat src = imread("bubbles.jpeg");
  imwrite("img/bubbles_on_black_background.pgm", src);
  // Mat dst1, dst2, dst3;

  // imshow("bubbles.jpg", src);
}