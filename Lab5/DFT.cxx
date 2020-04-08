#include <iostream>
//#include <vector>
//#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
Mat DFT(Mat img) {
	Mat imgGray, spectrum;
	cvtColor(img, imgGray, CV_RGB2GRAY);
	int m = getOptimalDFTSize(imgGray.rows);
	int n = getOptimalDFTSize(imgGray.cols);
	Mat temp;
	copyMakeBorder(imgGray, temp, 0, m - imgGray.rows, 0, n - imgGray.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(temp), Mat::zeros(temp.size(), CV_32F) };
	Mat  completeI;
	merge(planes, 2, completeI);
	dft(completeI, completeI);
	
	/*for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; i++) {
			completeI.at<Vec3b>(i,j)+=img.at<Vec3b>(i,j)*expf(2*CV_PI*())
		}
	}*/
	split(completeI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	spectrum = planes[0];
	spectrum += 1;
	log(spectrum, spectrum);
	spectrum = spectrum(Rect(0, 0, imgGray.cols, imgGray.rows));
	normalize(spectrum, spectrum, 0, 1, CV_MINMAX);

	int cx = spectrum.cols / 2;
	int cy = spectrum.rows / 2;

	Mat t;
	Mat q0(spectrum, Rect(0, 0, cx, cy));
	Mat q1(spectrum, Rect(cx, 0, cx, cy));
	Mat q2(spectrum, Rect(0, cy, cx, cy));
	Mat q3(spectrum, Rect(cx, cy, cx, cy));


	q0.copyTo(t);
	q3.copyTo(q0);
	t.copyTo(q3);

	q1.copyTo(t);
	q2.copyTo(q1);
	t.copyTo(q2);
	return spectrum;
}

int main() {
	Mat lena = imread("img/lena.pgm");
    
	Mat dftLena = DFT(lena);
	imshow("Lena", lena);
	imshow("Spectrum image of lena", dftLena);
	imwrite("dft.jpg", dftLena);
	waitKey(0);
	return 0;
}