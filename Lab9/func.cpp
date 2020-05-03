#include <vector>
#include "omp.h"
#include "func.hpp"

using namespace cv;
using namespace std;

Mat create_tmp(Mat src, Size ksize)
{
	int offsetX = ksize.height / 2, offsetY = ksize.width / 2;
	Mat tmp = Mat(src.rows + offsetX * 2, src.cols + offsetY * 2, src.type());

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			if (i < offsetX || j < offsetY)
				tmp.at<uchar>(i, j) = src.at<uchar>(i, j);
			else if (i + offsetX > src.rows - 1 || j + offsetY > src.cols - 1)
				tmp.at<uchar>(i + 2 * offsetX, j + 2 * offsetY) = src.at<uchar>(i, j);
			tmp.at<uchar>(i + offsetX, j + offsetY) = src.at<uchar>(i, j);
		}
	}

	return tmp;
}

void lab::convolution(Mat src, Mat &dst, Size ksize, uchar (*filter)(int, int, Mat, Size))
{
	Mat tmp;
	tmp = create_tmp(src, ksize);
	dst = Mat(src.size(), src.type());

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = filter(i, j, tmp, ksize);
		}
	}
}

void lab::convolution(Mat src, Mat &dst, Size ksize, double sigma, uchar (*filter)(int, int, Mat, Size, double))
{
	Mat tmp;
	tmp = create_tmp(src, ksize);
	dst = Mat(src.size(), src.type());

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = filter(i, j, tmp, ksize, sigma);
		}
	}
}

void lab::convolution(Mat src, Mat &d, Mat &dx, Mat &dy, Size ksize, int filterType, vector<uchar> (*filter)(int, int, Mat, Size, int))
{
	Mat tmp;
	tmp = create_tmp(src, ksize);
	d = Mat(src.size(), src.type());
	dx = Mat(src.size(), src.type());
	dy = Mat(src.size(), src.type());


	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			d.at<uchar>(i, j) = filter(i, j, tmp, ksize, filterType)[0];
			dx.at<uchar>(i, j) = filter(i, j, tmp, ksize, filterType)[1];
			dy.at<uchar>(i, j) = filter(i, j, tmp, ksize, filterType)[2];
		}
	}
}

void lab::convolution(Mat d, Mat dx, Mat dy, Mat &dst, uchar (*filter)(int, int, Mat, Mat, Mat))
{
	dst = Mat(d.size(), d.type());

	#pragma omp parallel for
	for (int i = 0; i < d.rows; ++i) {
		for (int j = 0; j < d.cols; ++j) {
			dst.at<uchar>(i, j) = filter(i, j, d, dx, dy);
		}
	}
}

void lab::threshold(Mat src, Mat &dst, double thres)
{
	dst = Mat(src.size(), src.type());

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<uchar>(i, j) = (double)src.at<uchar>(i, j) > thres ? 255 : 0;
		}
	}
}