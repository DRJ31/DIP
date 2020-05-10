#include <iostream>
#include <string>
#include "func.hpp"

using namespace std;
using namespace cv;


int selection()
{
  int selected;

  cout << "Select an operation: " << endl;
  cout << "1. Question 1" << endl;
  cout << "2. Question 2" << endl;
  cout << "3. Question 3" << endl;
  cout << "4. Question 4" << endl;
  cout << "Your selection: ";
  cin >> selected;
  return selected;
}

void operation(int selected)
{
  switch (selected)
  {
    case 1:
      Question1();
      break;
    case 2:
      Question2();
      break;
    case 3:
      Question3();
      break;
    case 4:
      Question4();
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
