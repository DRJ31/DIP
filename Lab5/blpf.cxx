#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

cv::Mat image_make_border(cv::Mat &src )
{
    int w=getOptimalDFTSize(src.cols);
    int h=getOptimalDFTSize(src.rows);
    Mat padded;
    copyMakeBorder(src,padded,0,h-src.rows,0,w-src.cols,BORDER_CONSTANT,Scalar::all(0));
    padded.convertTo(padded,CV_32FC1);
    return padded;
}

Mat frequency_filter(Mat &scr,Mat &blur)
{
  Mat plane[]={scr, Mat::zeros(scr.size() , CV_32FC1)};
  Mat complexIm;
  merge(plane,2,complexIm);
  dft(complexIm,complexIm);

  split(complexIm, plane);
  int cx=plane[0].cols/2;int cy=plane[0].rows/2;
  Mat part1_r(plane[0],Rect(0,0,cx,cy)); 
  Mat part2_r(plane[0],Rect(cx,0,cx,cy));
  Mat part3_r(plane[0],Rect(0,cy,cx,cy));
  Mat part4_r(plane[0],Rect(cx,cy,cx,cy));

  Mat temp;
  part1_r.copyTo(temp); //Upper left and lower right exchange position (real part)
  part4_r.copyTo(part1_r);
  temp.copyTo(part4_r);

  part2_r.copyTo(temp); //Upper right and bottom left exchange position (real part)
  part3_r.copyTo(part2_r);
  temp.copyTo(part3_r);

  Mat part1_i(plane[1], Rect(0,0,cx,cy)); //Element coordinates (cx, cy)
  Mat part2_i(plane[1],Rect(cx,0,cx,cy));
  Mat part3_i(plane[1],Rect(0,cy,cx,cy));
  Mat part4_i(plane[1],Rect(cx,cy,cx,cy));

  part1_i.copyTo(temp); //Upper left and lower right exchange position (imaginary part)
  part4_i.copyTo(part1_i);
  temp.copyTo(part4_i);

  part2_i.copyTo(temp); // upper right and lower left exchange position (imaginary part)
  part3_i.copyTo(part2_i);
  temp.copyTo(part3_i);

  Mat blur_r,blur_i,BLUR;
  multiply(plane[0], blur, blur_r); 
  multiply(plane[1], blur, blur_i); 
  Mat plane1[]={blur_r, blur_i};
  merge(plane1,2,BLUR);//The real and imaginary parts merge 

  magnitude(plane[0], plane[1], plane[0]);
  plane[0]+=Scalar::all(1); \
  log(plane[0], plane[0]); // The gray space of the float type is [0,1])
  normalize(plane[0], plane[0],1,0,CV_MINMAX); //normalized for easy display

  idft( BLUR, BLUR); //idft result is also plural
  split(BLUR, plane);//Separate channel, mainly get channel
  magnitude(plane[0],plane[1],plane[0]); //Amplitude (modulo)
  normalize(plane[0], plane[0],1,0,CV_MINMAX); //normalized for easy display
  return plane[0];//return parameters
}

//*****************Ideal low pass filter***********************
Mat ideal_low_kernel(Mat &scr,float sigma)
{
  Mat ideal_low_pass(scr.size(),CV_32FC1); //，CV_32FC1
  float d0=sigma;
  for(int i=0;i<scr.rows ; i++ ){
    for(int j=0; j<scr.cols ; j++ ){
      double d = sqrt(pow((i - scr.rows/2),2) + pow((j - scr.cols/2),2));
      if (d <= d0){
          ideal_low_pass.at<float>(i,j)=1;
      }else{
          ideal_low_pass.at<float>(i,j)=0;
      }
    }
  }
  string name = "ideal low pass filter d0=" + std::to_string(sigma);
  imshow(name, ideal_low_pass);
  return ideal_low_pass;
}

//ideal low pass filter
cv::Mat ideal_low_pass_filter(Mat &src, float sigma)
{

  Mat padded = image_make_border(src);
  Mat ideal_kernel=ideal_low_kernel(padded,sigma);
  Mat result = frequency_filter(padded,ideal_kernel);
  return result;
}


Mat butterworth_low_kernel(Mat &scr,float sigma, int n)
{
  Mat butterworth_low_pass(scr.size(),CV_32FC1); 
  double D0 = sigma;
  for(int i=0;i<scr.rows ; i++ ){
    for(int j=0; j<scr.cols ; j++ ){
      double d = sqrt(pow((i - scr.rows/2),2) + pow((j - scr.cols/2),2));
      butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(d / D0, 2 * n));
    }
  }

  String name = "Butterworth low pass filter d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
  imshow(name, butterworth_low_pass);
  return butterworth_low_pass;
}

//Butterworth low pass filter
Mat butterworth_low_paass_filter(Mat &src, float d0, int n)
{
  Mat padded = image_make_border(src);
  Mat butterworth_kernel=butterworth_low_kernel(padded,d0, n);
  Mat result = frequency_filter(padded,butterworth_kernel);
  return result;
}

Mat gaussian_low_pass_kernel(Mat scr,float sigma)
{
  Mat gaussianBlur(scr.size(),CV_32FC1); //，CV_32FC1
  float d0=2*sigma*sigma;
  for(int i=0;i<scr.rows ; i++ ){
    for(int j=0; j<scr.cols ; j++ ){
      float d=pow(float(i-scr.rows/2),2)+pow(float(j-scr.cols/2),2);
      gaussianBlur.at<float>(i,j)=expf(-d/d0);//expf is powered by e (must be float type)
    }
  }
//    Mat show = gaussianBlur.clone();
// // normalized to [0,255] for display
//    normalize(show, show, 0, 255, NORM_MINMAX);
// //Convert to CV_8U type
//    show.convertTo(show, CV_8U);
//    std::string pic_name = "gaussi" + std::to_string((int)sigma) + ".jpg";
//    imwrite( pic_name, show);

  imshow("Gaussian low-pass filter", gaussianBlur);
  return gaussianBlur;
}

//Gauss low pass
Mat gaussian_low_pass_filter(Mat &src, float d0)
{
  Mat padded = image_make_border(src);
  Mat gaussian_kernel=gaussian_low_pass_kernel(padded,d0);//ideal low pass filter
  Mat result = frequency_filter(padded,gaussian_kernel);
  return result;
}

Mat ideal_high_kernel(Mat &scr,float sigma)
{
  Mat ideal_high_pass(scr.size(),CV_32FC1); //，CV_32FC1
  float d0=sigma;
    for(int i=0;i<scr.rows ; i++ ){
      for(int j=0; j<scr.cols ; j++ ){
        double d = sqrt(pow((i - scr.rows/2),2) + pow((j - scr.cols/2),2));
        if (d <= d0){
            ideal_high_pass.at<float>(i,j)=0;
        }
        else{
          ideal_high_pass.at<float>(i,j)=1;
        }
      }
    }
  string name = "ideal high-pass filter d0=" + std::to_string(sigma);
    imshow(name, ideal_high_pass);
    return ideal_high_pass;
  }

//ideal high pass filter
cv::Mat ideal_high_pass_filter(Mat &src, float sigma)
{
  Mat padded = image_make_border(src);
  Mat ideal_kernel=ideal_high_kernel(padded,sigma);
  Mat result = frequency_filter(padded,ideal_kernel);
  return result;
}

Mat butterworth_high_kernel(Mat &scr,float sigma, int n)
{
  Mat butterworth_low_pass(scr.size(),CV_32FC1); //，CV_32FC1
  double D0 = sigma;//The smaller the radius D0, the larger the blur; the larger the radius D0, the smaller the blur
  for(int i=0;i<scr.rows ; i++ ){
    for(int j=0; j<scr.cols ; j++ ){
      double d = sqrt(pow((i - scr.rows/2),2) + pow((j - scr.cols/2),2));
      butterworth_low_pass.at<float>(i,j)=1.0 / (1 + pow(D0 / d, 2 * n));
    }
  }

  String name = "Butterworth high pass filter d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
  imshow(name, butterworth_low_pass);
  return butterworth_low_pass;
}

//Butterworth high pass filter
Mat butterworth_high_paass_filter(Mat &src, float d0, int n)
{
//H = 1 / (1+(D0/D)^2n) n represents the number of Butterworth filters
  Mat padded = image_make_border(src);
  Mat butterworth_kernel=butterworth_high_kernel(padded,d0, n);
  Mat result = frequency_filter(padded,butterworth_kernel);
  return result;
}

Mat gaussian_high_pass_kernel(Mat scr,float sigma)
{
  Mat gaussianBlur(scr.size(),CV_32FC1); //，CV_32FC1
  float d0=2*sigma*sigma;
  for(int i=0;i<scr.rows ; i++ ){
    for(int j=0; j<scr.cols ; j++ ){
      float d=pow(float(i-scr.rows/2),2)+pow(float(j-scr.cols/2),2);//molecular, calculation Pow must be float type
      gaussianBlur.at<float>(i,j)=1-expf(-d/d0);
    }
  }
  imshow("Gaussian high-pass filter", gaussianBlur);
  return gaussianBlur;
}

//Gauss Qualcomm
Mat gaussian_high_pass_filter(Mat &src, float d0)
{
  Mat padded = image_make_border(src);
  Mat gaussian_kernel=gaussian_high_pass_kernel(padded,d0);//ideal low pass filter
  Mat result = frequency_filter(padded,gaussian_kernel);
  return result;
}

int main( int argc, char *argv[])
{
    const char* filename = "img/lena.pgm";

    Mat input = imread(filename, IMREAD_GRAYSCALE);
    if( input.empty())
        return -1;
    imshow("input",input);//Show original image

    cv::Mat ideal_low = ideal_low_pass_filter(input, 30);
    ideal_low = ideal_low(cv::Rect(0,0, input.cols, input.rows));
    imshow("ideal low pass", ideal_low);

    cv::Mat bw_low = butterworth_low_paass_filter(input, 30, 2);
    bw_low = bw_low(cv::Rect(0,0, input.cols, input.rows));
    imshow("Butterworth Low Pass", bw_low);

    cv::Mat gaussion_low = gaussian_low_pass_filter(input, 30);
    gaussion_low = gaussion_low(cv::Rect(0,0, input.cols, input.rows));
    imshow("Gauss Lowpass", gaussion_low);

    waitKey();
    return 0;
}