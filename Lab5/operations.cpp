#include <iostream>
#include "func.hpp"
#include "operations.hpp"

using namespace std;
using namespace cv;

void lab::DFT(cv::String filename)
{
  Mat src = imread(filename, 0);
  Mat dst1, dst2;

  lab::dft(src, dst1, dst2);
  lab::magnitude(dst1, dst2, dst1);
  dst1 += 1;
  lab::log(dst1, dst1);

  lab::shift(dst1, dst1);

  // Normalize points to show image on imshow
  lab::normalize(dst1, dst1);


  imshow("Spectrum", dst1);
}

void lab::PhaseReconstruct(cv::String filename)
{
  Mat src = imread(filename, 0);
  Mat tmp1, tmp2, dst1, dst2;

  lab::dft(src, tmp1, tmp2);
  
  lab::magnitude(tmp1, tmp2, dst1);
  lab::norm_angle(dst1, dst1);
  lab::idft(dst1, tmp1, tmp2);

  lab::magnitude(tmp1, tmp2, dst1);
  lab::normalize(dst1, dst1);
  lab::shift(dst1, dst1);

  imshow("Reconstruct", dst1);
}