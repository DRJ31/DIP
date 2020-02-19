#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main()
{
  // 读取源图像并转化为灰度图像
  IplImage *img;
  img = cvvLoadImage("img/lena.jpg");

  // 判断文件是否读入正确
  if (!img)
    return 1;

  // 图像显示
  cvvShowImage("srcImage", img);
  
  // 等待键盘键入
  waitKey(0);
  return 0;
}