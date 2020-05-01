#include "omp.h"
#include "func.hpp"

using namespace cv;


Mat create_tmp(Mat src, Size ksize)
{
	int offsetX = ksize.height / 2, offsetY = ksize.width / 2;
	Mat tmp = Mat(src.rows + offsetX * 2, src.cols + offsetY * 2, src.type());

	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
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
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
		{
			dst.at<uchar>(i, j) = filter(i, j, tmp, ksize);
		}
	}
}