#include <iostream>
#include "operations.hpp"

using namespace std;
using namespace cv;


int selection()
{
  int selected;
  cout << "Select an operation: " << endl;
  cout << "1. HPF" << endl;
  cout << "2. Homomorphic" << endl;
  cout << "3. Sinusoidal Noise" << endl;
  cout << "4. Face" << endl;
  cout << "Your selection: ";
  cin >> selected;
  return selected;
}

void operation(int selected)
{
  switch (selected)
  {
    case 1:
      lab::HPF("img/fingerprint1.pgm");
      break;
    case 2:
      lab::HomomorphicFilter("img/bridge.pgm");
      break;
    case 3:
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
