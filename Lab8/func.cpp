#include "func.hpp"

using namespace cv;

bool lab::checkBorder(Mat src, int x, int y, int xy, int lm)
{
  if (lm == CHECK_LESS) {
    if (xy == CHECK_X) 
      return x - 1 < 0 ? true : (int)src.at<uchar>(x - 1, y) == 0;
    else if (xy == CHECK_Y)
      return y - 1 < 0 ? true : (int)src.at<uchar>(x, y - 1) == 0;
  } else if (lm == CHECK_MORE) {
    if (xy == CHECK_X) 
      return x + 1 >= src.rows ? true : (int)src.at<uchar>(x + 1, y) == 0;
    else if (xy == CHECK_Y)
      return y + 1 >= src.cols ? true : (int)src.at<uchar>(x, y + 1) == 0;
  }
  return false;
}