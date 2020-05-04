#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
int main(){
    Mat input_image = imread("9190.png", 0);
    Mat kernel = (Mat_<int>(9, 9) <<
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0);
    Mat output_image;
    morphologyEx(input_image, output_image, MORPH_HITMISS, kernel);
    imshow("Original", input_image);
    imshow("Hit or Miss", output_image);
    waitKey(0);
    return 0;
}