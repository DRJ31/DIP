#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "func.hpp"

using namespace std;

int selection()
{
  int select;
  cout << "Select an operation: " << endl;
  cout << "1. Sharpen Image" << endl;
  cout << "2. Gamma Correction" << endl;
  cout << "3. Histogram Enhancement" << endl;
  cout << "Your selection: ";
  cin >> select;
  return select;
}

void operation(int selected, cv::String filename)
{
  switch (selected)
  {
    case 1:
      lab::Sharpen(filename);
      break;
    case 2:
      lab::Gamma(filename);
      break;
    case 3:
      lab::Histogram(filename);
      break;
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