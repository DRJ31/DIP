#include <numeric>
#include <cmath>
#include "func.hpp"

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
	if (!dst.data) {
    dst = Mat(src.size(), src.type());
  }

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = (double)src.at<uchar>(i, j) > thres ? 255 : 0;
		}
	}
}

void movingAvg(Mat src, Mat &dst, int steps, double b)
{
  dst = Mat(src.size(), src.type());

  uchar *srcData = src.data;
  uchar *dstData = dst.data;
  double preAvg = srcData[0] * 1.0 / steps;
  double avg = 0;

  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      int index = i * src.cols + j;

      double dif;
      if (index < steps + 1) 
        dif = srcData[index];
      else
        dif = srcData[index] - srcData[index - steps - 1];

      dif /= steps;
      avg = preAvg + dif;
      preAvg = avg;

      dstData[index] = srcData[index] > b * avg ? 255 : 0;
    }
  }
}

void regionGrow(Mat src, Mat &dst, SeedPoint pt, int thres)
{
  vector<SeedPoint> growPts, offsets;
  SeedPoint growPt;
  uchar hasGrown, curValue;
  uchar srcValue = src.at<uchar>(pt.x, pt.y);
  dst = Mat(src.size(), src.type());
  growPts.push_back(pt);
  dst.at<uchar>(pt.x, pt.y) = 255;

  // Generate elements in offsets
  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {
      if (i == 0 && j == 0)
        continue;
      
      SeedPoint point{i, j};
      offsets.push_back(point);
    }
  }

  while (!growPts.empty()) {
    pt = growPts.back();
    growPts.pop_back();

    for (auto offset : offsets) {
      growPt.x = pt.x + offset.x;
      growPt.y = pt.y + offset.y;
      if (growPt.x < 0 || growPt.y < 0 || growPt.x >= src.rows || growPt.y >= src.cols)
        continue;

      hasGrown = dst.at<uchar>(growPt.x, growPt.y);

      if (hasGrown == 0) {
        curValue = src.at<uchar>(growPt.x, growPt.y);
        if (abs(srcValue - curValue) < thres) {
          dst.at<uchar>(growPt.x, growPt.y) = 255;
          growPts.push_back(growPt);
        }
      }
    }
  }
}