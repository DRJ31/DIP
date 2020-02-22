#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "enlarge/enlarge.hpp"

using namespace cv;
using namespace std;


void enlarge(vector<cv::String> filenames, int selected) 
{
  switch(selected)
  {
    case 1:
      lab::PixelReplication(filenames);
      return;
    default:
      return;
  }
}


int selection() 
{
  int selected = 0;
  cout << "Please select an enlargement algorithm: " << endl;
  cout << "1. Pixel Replication" << endl;
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
  enlarge(filenames, selected);

  waitKey(0);
  return 0;
}