#include <iostream>
#include "func.hpp"

using namespace std;
using namespace cv;


int selection()
{
  int selected;
  cout << "Select an operation: " << endl;
  cout << "1. Question1" << endl;
  cout << "2. Question2" << endl;
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
