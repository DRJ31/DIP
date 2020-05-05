#include <numeric>
#include <cmath>
#include "func.hpp"
#include "omp.h"

using namespace cv;
using namespace std;

vector<int> getHist(Mat src)
{
  vector<int> results = vector<int>(256, 0);

  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      results[src.at<uchar>(i, j)] += 1;
    }
  }
  return results;
}

uchar otsu_threshold(vector<int> histogram, Mat src)
{
  int sumLess = 0, count = 0, sum = 0;
  uchar maxThres = 0;
  double maxVar = 0, internVar = 0;
  double avgLess = 0, avgMore = 0;

  for (int i = 1; i < 256; ++i){
    sum += i * histogram[i];
  }

  for (int i = 0; i < 256; ++i) {
    count += histogram[i];
    
    if (count == 0 || src.rows * src.cols - count == 0)
      continue;
    
    sumLess += i * histogram[i];
    avgLess = sumLess / count;
    avgMore = (sum - sumLess) / (src.rows * src.cols - count);
    internVar = count * (src.rows * src.cols - count) * pow(avgMore - avgLess, 2);

    if (internVar >= maxVar) {
      maxThres = i;
      maxVar = internVar;
    }
  }

  return maxThres;
}

void lab::threshold(Mat src, Mat &dst, uchar thres)
{
	dst = Mat(src.size(), src.type());

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = (double)src.at<uchar>(i, j) > thres ? 255 : 0;
		}
	}
}