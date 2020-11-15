#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace cv;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;
  struct timespec begin, end;
  if(argc<3){
     printf("usage: ./hough_circle imagefile numIterations \n");
     return -1;
  }
  int iterations = atoi(argv[2]);
  printf("number of iterations is %d\n",iterations);

  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  std::vector<Vec3f> circles;

  //time the transform
  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);  
  for(int i=0; i<iterations; i++){
     // Apply the Hough Transform to find the circles
     HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );
  }
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  //display runtime
  std::cout<<"elapsed time was "<<((end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec - begin.tv_sec)) <<std::endl;  

  //show the results
  namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src );
  waitKey(0);

  return 0;
}
