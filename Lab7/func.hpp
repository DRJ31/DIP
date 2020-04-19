#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <type_traits>
#include "omp.h"

namespace lab 
{
  template<typename T>
  class Filter {
    public:
      static cv::Mat create_tmp(cv::Mat src, cv::Size ksize);

      static T median(int x, int y, cv::Mat tmp, cv::Size ksize);

			static T arithmeticMean(int x, int y, cv::Mat tmp, cv::Size ksize);

			static T geometricMean(int x, int y, cv::Mat tmp, cv::Size ksize);

			static T alphaTrimmed(int x, int y, int d, cv::Mat tmp, cv::Size ksize);

			static T adaptiveMedian(int x, int y, cv::Mat tmp, cv::Size ksize);

      static void convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, T (*filter)(int, int, cv::Mat, cv::Size));

			static void convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, int d, T (*filter)(int, int, int, cv::Mat, cv::Size));

			static cv::Mat recoverSrc(cv::Mat tmp, cv::Size ksize);
  };

  void NoiseCancel();

	void FilterLena();
}


template<typename T>
cv::Mat lab::Filter<T>::create_tmp(cv::Mat src, cv::Size ksize)
{
	int offsetX = ksize.height / 2, offsetY = ksize.width / 2;
	cv::Mat tmp = cv::Mat(src.rows + offsetX * 2, src.cols + offsetY * 2, src.type());

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			if (i < offsetX || j < offsetY)
				tmp.at<T>(i, j) = src.at<T>(i, j);
			else if (i + offsetX > src.rows - 1 || j + offsetY > src.cols - 1)
				tmp.at<T>(i + 2 * offsetX, j + 2 * offsetY) = src.at<T>(i, j);
			tmp.at<T>(i + offsetX, j + offsetY) = src.at<T>(i, j);
		}
	}

	return tmp;
}


template<typename T>
T lab::Filter<T>::median(int x, int y, cv::Mat tmp, cv::Size ksize)
{
	std::vector<T> points;
	int height = ksize.height, width = ksize.width;

	for (int i = x; i < x + height; ++i) {
		for (int j = y; j < y + width; ++j) {
			points.push_back(tmp.at<T>(i, j));
		}
	}

	std::sort(points.begin(), points.end());
	return points[height * width / 2];
}

template<typename T>
void lab::Filter<T>::convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, T (*filter)(int, int, cv::Mat, cv::Size))
{
	cv::Mat tmp;
	tmp = lab::Filter<T>::create_tmp(src, ksize);

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<T>(i, j) = filter(i, j, tmp, ksize);
		}
	}
}

template<typename T>
void lab::Filter<T>::convolution(cv::Mat src, cv::Mat &dst, cv::Size ksize, int d, T (*filter)(int, int, int, cv::Mat, cv::Size))
{
	cv::Mat tmp;
	tmp = create_tmp(src, ksize);

	#pragma omp parallel for
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			dst.at<T>(i, j) = filter(i, j, d, tmp, ksize);
		}
	}
}

template<typename T>
T lab::Filter<T>::arithmeticMean(int x, int y, cv::Mat tmp, cv::Size ksize)
{
	int sum = 0;

	for (int i = x; i < x + ksize.height; ++i) {
		for (int j = y; j < y + ksize.width; ++j) {
			sum += tmp.at<T>(i, j);
		}
	}

	sum /= ksize.height * ksize.width;
	T result = (T)sum;

	return result;
}

template<typename T>
T lab::Filter<T>::geometricMean(int x, int y, cv::Mat tmp, cv::Size ksize)
{
	double sum = 1;

	for (int i = x; i < x + ksize.height; ++i) {
		for (int j = y; j < y + ksize.width; ++j) {
			sum *= tmp.at<T>(i, j);
		}
	}

	sum = pow(sum, 1.0 / 9);
	T result = (T)sum;

	return result;
}

template<typename T>
T lab::Filter<T>::alphaTrimmed(int x, int y, int d, cv::Mat tmp, cv::Size ksize)
{
	std::vector<T> points;
	int height = ksize.height, width = ksize.width;

	for (int i = x; i < x + ksize.height; ++i) {
		for (int j = y; j < y + ksize.width; ++j) {
			points.push_back(tmp.at<T>(i, j));
		}
	}

	std::sort(points.begin(), points.end());

	double sum = 0;
	for (unsigned int i = d; i < points.size() - d; ++i) {
		sum += points[i];
	}

	sum /= height * width - 2 * d;
	return (T)sum;	
}

template<typename T>
T lab::Filter<T>::adaptiveMedian(int x, int y, cv::Mat tmp, cv::Size ksize)
{
	std::vector<T> points;
	int height = ksize.height, width = ksize.width;
	cv::Mat src = lab::Filter<T>::recoverSrc(tmp, ksize);

	for (int i = x; i < x + ksize.height; ++i) {
		for (int j = y; j < y + ksize.width; ++j) {
			points.push_back(tmp.at<T>(i, j));
		}
	}

	std::sort(points.begin(), points.end());

	T med = points[height * width / 2];
	if (med > points[0] && points[height * width - 1] > med) {
		T point = src.at<T>(x, y);
		return point > points[0] && points[height * width - 1] > point ? point : med;
	} else if (ksize.height + 1 <= src.rows && ksize.width + 1 <= src.cols) {
		cv::Size nSize = cv::Size(ksize.height + 1, ksize.width + 1);
		cv::Mat nTmp = lab::Filter<T>::create_tmp(src, nSize);
		lab::Filter<T>::adaptiveMedian(x, y, nTmp, nSize);
	}
	return med;
}

template<typename T>
cv::Mat lab::Filter<T>::recoverSrc(cv::Mat tmp, cv::Size ksize)
{
	int h = ksize.height / 2, w = ksize.width / 2;
	cv::Mat src = cv::Mat(tmp.rows - 2 * h, tmp.cols - 2 * w, tmp.type());

	for (int i = h; i < tmp.rows - h; ++i) {
		for (int j = w; j < tmp.cols - w; ++j) {
			src.at<T>(i - h, j - w) = tmp.at<T>(i, j);
		}
	} 

	return src;
}
