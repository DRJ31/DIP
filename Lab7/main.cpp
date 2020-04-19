#include <iostream>
#include "func.hpp"

using namespace std;
using namespace cv;
using namespace lab;

void hw5() 
{
  Mat src = imread("img/hw5.png");
  Mat dst = Mat(src.size(), CV_8UC1);
  ostringstream os;
  int sizes[] = {3,5,9};

  for (auto size : sizes) {
    Filter<uchar>::convolution(src, dst, Size(size, size), Filter<uchar>::geometricMean);
    os.str("");
    os << "gMean" << size << ".jpg";
    imwrite(os.str(), dst);
  }
}


int selection()
{
  int selected;
  cout << "Select an operation: " << endl;
  cout << "1. Question1" << endl;
  cout << "2. Question2" << endl;
  cout << "3. Homework5" << endl;
  cout << "Your selection: ";
  cin >> selected;
  return selected;
}

void operation(int selected)
{
  switch (selected)
  {
    case 1:
      lab::NoiseCancel();
      break;
    case 2:
      lab::FilterLena();
      break;
    case 3:
      hw5();
    default:
      break;
  }
}


int main() 
{
  int selected = selection();
  operation(selected);
  waitKey(0);
  return 0;
}
