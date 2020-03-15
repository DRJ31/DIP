#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "func.hpp"

using namespace std;

int selection()
{
  int select;
  cout << "Select an operation: " << endl;
  cout << "1. Translation" << endl;
  cout << "2. Rotation" << endl;
  cout << "3. Shear" << endl;
  cout << "4. Smoothing" << endl;
  cout << "Your selection: ";
  cin >> select;
  return select;
}

void operation(int selected, cv::String filename)
{
  switch (selected)
  {
    case 1:
      lab::Translation(filename);
      break;
    case 2:
      lab::Rotation(filename);
      break;
    case 3:
      lab::Shear(filename);
      break;
    case 4:
      lab::Smoothing(filename);
    default:
      break;
  }
}

int main()
{
  string filename = "img/lena.jpg";
  // cout << "Please input the filename of picture: " << endl;
  // cin >> filename;

  operation(selection(), filename);
  return 0;
}