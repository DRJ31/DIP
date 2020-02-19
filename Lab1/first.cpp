/* First OpenCV program. */ 
#include <iostream> 
#include <opencv2/opencv.hpp> 

using namespace cv;

int main(int argc, char *argv[])
{
  printf("Hello world\n");
  Mat image = imread("img/lena.jpg");
  if (image.empty())
  {
    std::cout << "Hey! Can't read the image!" << std::endl;
    system("PAUSE");
    return EXIT_FAILURE;
  }
  namedWindow("My Image");
  imshow("My Image", image);
  waitKey(5000);
  return EXIT_SUCCESS;
}