#include "operations.hpp"
#include "func.hpp"

using namespace cv;

void lab::HPF(cv::String filename)
{
    Mat src = imread(filename, 0);

    resize(src, src, Size(), 0.25, 0.25);
    imshow("src",src);
    src.convertTo(src, CV_64FC1);

    int height = 2 * src.rows, width = 2 * src.cols;
    
    // Preparation for dft
    Mat padded;
    copyMakeBorder(src, padded, 0, height-src.rows, 0, width-src.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat tmp[] = {padded, Mat::zeros(padded.size(),CV_64FC1)};
    Mat complexI;
    merge(tmp, 2, complexI);
    dft(complexI, complexI);

    split(complexI, tmp);
    lab::shift(tmp[0], tmp[0]);
    lab::shift(tmp[1], tmp[1]);

    Mat butter_kernel = Mat(padded.size(), CV_64FC1);
    double D0 = 50;
    int n = 4;
    for(int i = 0; i < butter_kernel.rows; ++i){
        for(int j=0; j < butter_kernel.cols; ++j){
            double d = sqrt(pow(i - height / 2, 2) + pow(j - width / 2, 2));
            butter_kernel.at<double>(i, j) = 1.0 / (1 + pow(D0 / d, 2 * n));
        }
    }

    multiply(tmp[0], butter_kernel, tmp[0]);
    multiply(tmp[1], butter_kernel, tmp[1]);
    merge(tmp, 2, complexI);

    idft(complexI, complexI);

    Mat dst[2];
    split(complexI, dst);
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            dst[0].at<double>(i, j) *= pow(-1, i + j);
        }
    }

    lab::threshold(dst[0], dst[0]);
    lab::normalize(dst[0], dst[0]);
    dst[0] = dst[0](Rect(0,0,src.cols, src.rows));
    dst[0].convertTo(dst[0], CV_8UC1);
    // imwrite("dst.jpg",dst[0]);
    imshow("dst", dst[0]);
}