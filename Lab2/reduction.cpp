#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "reduce/reduction.hpp"

using namespace cv;
using namespace std;


void reduce(vector<cv::String> filenames, int selected) 
{
  switch(selected)
  {
    case 1:
      lab::AlternativeLine(filenames);
      return;
    case 2:
      lab::FractionalLinearReduction(filenames);
      return;
    default:
      return;
  }
}


int selection() 
{
  int selected = 0;
  cout << "Please select an reduction algorithm: " << endl;
  cout << "1. Alternative Line Reduction" << endl;
  cout << "2. Fractional Line Reduction" << endl;
  cout << "Selection: ";
  cin >> selected;
  return selected;
}


int main()
{
  vector<cv::String> filenames;
  cv::String pattern = "img/*.pgm";
  Mat srcImg, outImg;

  // Get all pgm files in glob
  glob(pattern, filenames);

  // Select an algorithm
  int selected = selection();

  // Main function of the algorithm
  reduce(filenames, selected);

  waitKey(0);
  return 0;
}