#include "func.hpp"

using namespace cv;

void lab::Morphs() 
{
  Mat src1 = imread("img/noisy_fingerprint.pgm");
  Mat src2 = imread("img/noisy_rectangle.pgm");
  Mat dst1, dst2;

  // Show src image
  imshow("fingerprint.jpg", src1);
  imshow("rect.jpg", src2);

  Mat element1 = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
  Mat element2 = getStructuringElement(MORPH_RECT, cv::Size(30, 30));

  // Erode operation
  erode(src1, dst1, element1);
  erode(src2, dst2, element2);
  imshow("erode_finger.jpg", dst1);
  imshow("erode_rect.jpg", dst2);

  // Dilate operation
  dilate(src1, dst1, element1);
  dilate(src2, dst2, element2);
  imshow("dilate_finger.jpg", dst1);
  imshow("dilate_rect.jpg", dst2);

  // Opening operation
  erode(src1, dst1, element1);
  dilate(dst1, dst1, element1);
  erode(src2, dst2, element2);
  dilate(dst2, dst2, element2);
  imshow("opening_finger.jpg", dst1);
  imshow("opening_rect.jpg", dst2);

  // Closing operation
  dilate(src1, dst1, element1);
  erode(dst1, dst1, element1);
  dilate(src2, dst2, element2);
  erode(dst2, dst2, element2);
  imshow("closing_finger.jpg", dst1);
  imshow("closing_rect.jpg", dst2);
}