#include "enlarge.hpp"
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

double bicubicPoly(double x, double a = -0.5)
{
  if (abs(x) <= 1.0)
    return (a + 2) * pow(abs(x), 3) - (a + 3) * pow(abs(x), 2) + 1;
  else if (abs(x) < 2.0)
    return a * pow(abs(x), 3) - 5 * a * pow(abs(x), 2) + 8 * a * abs(x) - 4 * a;
  else
    return 0;
}

void bicubic(Mat src, Mat &dst, double ratio)
{
  int rows = floor(src.rows * ratio), cols = floor(src.cols * ratio);
  dst = Mat(rows, cols, src.type());

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      double x = i / ratio, y = j / ratio;
      if (x < 1)
        x += 1;
      if (y < 1)
        y += 1;
      if (x > rows - 3)
        x = rows - 3;
      if (y > cols - 3)
        y = cols - 3;

      double x1 = 1 + x - floor(x);
      double x2 = x - floor(x);
      double x3 = floor(x) + 1 - x;
      double x4 = floor(x) + 2 - x;

      double y1 = 1 + y - floor(y);
      double y2 = y - floor(y);
      double y4 = floor(y) + 2 - y;
      double y3 = floor(y) + 1 - y;

      vector<double> left = {bicubicPoly(x1), bicubicPoly(x2), bicubicPoly(x3), bicubicPoly(x4)};
      vector<double> right = {bicubicPoly(y1), bicubicPoly(y2), bicubicPoly(y3), bicubicPoly(y4)};
      vector<Vec3b> middle = {
        src.at<Vec3b>(x - x1, y - y1), src.at<Vec3b>(x - x2, y - y1), src.at<Vec3b>(x + x3, y - y1), src.at<Vec3b>(x + x4, y - y1),
        src.at<Vec3b>(x - x1, y - y2), src.at<Vec3b>(x - x2, y - y2), src.at<Vec3b>(x + x3, y - y2), src.at<Vec3b>(x + x4, y - y2),
        src.at<Vec3b>(x - x1, y + y3), src.at<Vec3b>(x - x2, y + y3), src.at<Vec3b>(x + x3, y + y3), src.at<Vec3b>(x + x4, y + y3),
        src.at<Vec3b>(x - x1, y + y4), src.at<Vec3b>(x - x2, y + y4), src.at<Vec3b>(x + x3, y + y4), src.at<Vec3b>(x + x4, y + y4)
      };

      Vec3b val = Vec3b();

      for (uint m = 0; m < left.size(); ++m)
      {
        for (uint n = 0; n < right.size(); ++n)
        {
          for (int p = 0; p < 3; ++p)
          {
            val[p] += round(left[m] * right[n] * middle[4 * m + n][p]);
          }
        }
      }

      dst.at<Vec3b>(i, j) = val;
    }
  }
}

void lab::BicubicInterpolation(vector<cv::String> filenames)
{
  Mat srcImg, outImg;
  double ratio;
  cout << "Input ratio you want to expand: ";
  cin >> ratio;
  if (ratio < 1)
  {
    cout << "Ratio should be larger than 1." << endl;
    return;
  }

  for (auto filename : filenames)
  {
    srcImg = imread(filename);
    bicubic(srcImg, outImg, ratio);
    imshow(filename, outImg);
  }
}