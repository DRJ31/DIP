#include <iostream>
#include <vector>
#include <cmath>
#include "func.hpp"

using namespace std;
using namespace cv;


Mat create_tmp(Mat src)
{
  Mat tmp = Mat(src.rows + 2, src.cols + 2, src.type());

  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      if (i < 1 || j < 1)
        tmp.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
      else if (i + 1 > src.rows - 1 || j + 1 > src.cols - 1)
        tmp.at<Vec3b>(i + 2, j + 2) = src.at<Vec3b>(i, j);
      tmp.at<Vec3b>(i + 1, j + 1) = src.at<Vec3b>(i, j);
    }
  }

  return tmp;
}


Mat vec_to_mat(vector<int> vec, Size size)
{
  Mat result = Mat(size, CV_32SC1);
  
  for (int i = 0; i < size.height; ++i) {
    for (int j = 0; j < size.width; ++j) {
      result.at<int>(i, j) = vec[i * size.width + j];
    }
  }
  return result;
}


vector<int> conv(int x, int y, Mat tmp, Mat matrix)
{
  vector<int> point = {0,0,0};

  for (int i = x; i < x + 3; ++i) {
    for (int j = y; j < y + 3; ++j) {
      for (int m = 0; m < 3; ++m) {
        point[m] += tmp.at<Vec3b>(i, j)[m] * matrix.at<int>(i - x, j - y);
      }
    }
  }

  return point;
}


void Laplacian(Mat src, Mat mat)
{
  Mat tmp, dst;
  tmp = create_tmp(src);
  dst = Mat(src.size(), src.type());
  
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      vector<int> p = conv(i, j, tmp, mat);
      for (int m = 0; m < 3; ++m) {
        dst.at<Vec3b>(i, j)[m] = src.at<Vec3b>(i, j)[m] + abs(p[m]);
      }
    }
  }

  imshow("Laplacian", dst);
}


void Sobel(Mat src, Mat mat1, Mat mat2)
{
  Mat tmp, dst;
  tmp = create_tmp(src);
  dst = Mat(src.size(), src.type());

  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      vector<int> gx = conv(i, j, tmp, mat1);
      vector<int> gy = conv(i, j, tmp, mat2);
      for (int m = 0; m < 3; ++m) {
        dst.at<Vec3b>(i, j)[m] = sqrt(pow(gx[m], 2) + pow(gy[m], 2));
      }
    }
  }

  imshow("Sobel", dst);
}


void lab::Sharpen(cv::String filename)
{
  int selected;
  vector<int> laplacian = {0,1,0,1,-4,1,0,1,0};
  vector<int> sobelx = {-1,-2,-1,0,0,0,1,2,1};
  vector<int> sobely = {-1,0,1,-2,0,2,-1,0,1};
  Mat src = imread(filename);

  while (true) {
		cout << "Select a sharpen filter: " << endl;
		cout << "1. Laplacian" << endl;
		cout << "2. Sobel" << endl;
		cout << "Your selection: ";
		cin >> selected;
		if (selected > 0 && selected < 3) break;
	}

  if (selected == 1)
    Laplacian(src, vec_to_mat(laplacian, Size(3, 3)));
  else if (selected == 2)
    Sobel(src, vec_to_mat(sobelx, Size(3, 3)), vec_to_mat(sobely, Size(3, 3)));
  
  waitKey(0);
}