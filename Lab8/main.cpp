#include <iostream>
#include "func.hpp"

using namespace std;
using namespace cv;


int selection()
{
  int selected;
  cout << "Select an operation: " << endl;
  cout << "1. Binary Operations" << endl;
  cout << "2. Extract boundries" << endl;
  cout << "3. Count pixels" << endl;
  cout << "4. Seperate" << endl;
  cout << "Your selection: ";
  cin >> selected;
  return selected;
}

void operation(int selected)
{
  switch (selected)
  {
    case 1:
      break;
    case 2:
      break;
    case 3:
      lab::CountPixels();
      break;
    case 4:
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
