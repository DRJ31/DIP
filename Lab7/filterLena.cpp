#include <iostream>
#include "func.hpp"

using namespace std;
using namespace cv;
using namespace lab;

void lab::FilterLena()
{
  vector<cv::String> filenames = {"img/lenaD1.pgm", "img/lenaD2.pgm", "img/lenaD3.pgm"};
  vector<Mat> srcs(filenames.size());
  Mat dst;
  ostringstream os;

  // Read files
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    srcs[i] = imread(filenames[i], 0);
    os.str("");
    os << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), srcs[i]);
    os.clear();
  }

  // Median Filter
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    dst = Mat(srcs[i].size(), CV_8UC1);
    Filter<uchar>::convolution(srcs[i], dst, Size(3, 3), Filter<uchar>::median);
    os.str("");
    os << "median" << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), dst);
    os.clear();
  }

  // Arithmetic Mean Filter
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    dst = Mat(srcs[i].size(), CV_8UC1);
    Filter<uchar>::convolution(srcs[i], dst, Size(3, 3), Filter<uchar>::arithmeticMean);
    os.str("");
    os << "aMean" << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), dst);
    os.clear();
  }

  // Geometric Mean Filter
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    dst = Mat(srcs[i].size(), CV_8UC1);
    Filter<uchar>::convolution(srcs[i], dst, Size(3, 3), Filter<uchar>::geometricMean);
    os.str("");
    os << "gMean" << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), dst);
    os.clear();
  }

  // Alpha-trimmed mean Filter
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    dst = Mat(srcs[i].size(), CV_8UC1);
    Filter<uchar>::convolution(srcs[i], dst, Size(3, 3), 2, Filter<uchar>::alphaTrimmed);
    os.str("");
    os << "atMean" << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), dst);
    os.clear();
  }

  // Adaptive Median Filter
  for (unsigned int i = 0; i < filenames.size(); ++i) {
    dst = Mat(srcs[i].size(), CV_8UC1);
    Filter<uchar>::convolution(srcs[i], dst, Size(2, 2), Filter<uchar>::adaptiveMedian);
    os.str("");
    os << "aMedian" << filenames[i].substr(4, filenames[i].length() - 8) << ".jpg";
    imshow(os.str(), dst);
    os.clear();
  }
}