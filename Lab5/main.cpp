#include <iostream>
#include "func.hpp"

using namespace std;
using namespace cv;


int selection()
{
  int selected;
  cout << "Select an operation: " << endl;
  cout << "1. DFT" << endl;
  cout << "2. Phase Angle" << endl;
  cout << "3. Filter" << endl;
  cout << "Your selection: ";
  cin >> selected;
  return selected;
}

void operation(int selected, cv::String filename)
{
  switch (selected)
  {
    case 1:
      lab::DFT(filename);
      break;
    default:
      break;
  }
}


int main() 
{
  cv::String filename = "img/lena.pgm";

  int selected = selection();
  operation(selected, filename);
  waitKey(0);
  return 0;
}
