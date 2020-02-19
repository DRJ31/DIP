#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main()
{ 
  // Read origin image
  Mat srcImage = imread("img/lena.jpg");

  // Judge if the file has correcly read
  if (!srcImage.data)
    return 1;

  // Show image
  imshow("srcImage", srcImage);

  // Wait for input of keyboard
  waitKey(0);
  return 0;
}