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
    case 2:
      lab::NearestNeighbour(filenames);
      return;
    case 3:
      lab::BilinearInterpolation(filenames);
      return;
    case 4:
      lab::BicubicInterpolation(filenames);
      return;
    // case 5:
    //   lab::FractionalLinearEnlargement(filenames);
    //   return;
    default:
      return;
  }
}


int selection() 
{
  int selected = 0;
  cout << "Please select an enlargement algorithm: " << endl;
  cout << "1. Pixel Replication" << endl;
  cout << "2. Nearest Neighbour" << endl;
  cout << "3. Bilinear Interpolation" << endl;
  cout << "4. Bicubic Interpolation" << endl;
  cout << "5. Fractional Linear Enlargement" << endl;
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