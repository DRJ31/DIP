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
  dst1.convertTo(dst1, CV_8UC1);

  imshow("Spectrum", dst1);
}

void lab::PhaseReconstruct(cv::String filename)
{
  Mat src = imread(filename, 0);
  Mat tmp1, tmp2, dst1, dst2;

  lab::dft(src, tmp1, tmp2);
  lab::one_amptitude(tmp1, tmp2, dst2);
  lab::magnitude(tmp1, tmp2, dst1);
  lab::norm_angle(dst1, dst1);

  lab::idft(dst1, tmp1, tmp2);
  lab::magnitude(tmp1, tmp2, dst1);
  lab::normalize(dst1, dst1);

  lab::idft(dst2, tmp1, tmp2);
  lab::magnitude(tmp1, tmp2, dst2);
  lab::normalize(dst2, dst2);

  dst1.convertTo(dst1, CV_8UC1);
  dst2.convertTo(dst1, CV_8UC1);
  lab::shift(dst1, dst1);

  imshow("Reconstruct", dst1);
  imshow("Amptitude", dst2);
}


void lab::LPF(cv::String filename)
{
  Mat src = imread(filename, 0);
  imshow("Origin", src);//Show original image

  Mat ideal_low = lab::ideal_low_pass_filter(src, 30);
  cout << "ideal" << endl;
  ideal_low = ideal_low(cv::Rect(0,0, src.cols, src.rows));
  imshow("IDLPF", ideal_low);

  Mat bw_low = lab::butterworth_low_paass_filter(src, 30, 2);
  cout << "bw" << endl;
  bw_low = bw_low(cv::Rect(0,0, src.cols, src.rows));
  imshow("BLPF", bw_low);

  Mat gaussion_low = lab::gaussian_low_pass_filter(src, 30);
  cout << "gau" << endl;
  gaussion_low = gaussion_low(cv::Rect(0,0, src.cols, src.rows));
  imshow("GLPF", gaussion_low);
}