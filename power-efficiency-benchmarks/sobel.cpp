#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <omp.h>
	
using namespace cv;
	
/**
 * @function main
 */
int main( int argc, char** argv )
{

  Mat src, src_gray;
  Mat grad; 
  char window_name[] = "Sobel Demo - Simple Edge Detector";
  //char* window_name = "Sobel Demo - Simple Edge Detector";
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  int c;
  int thread_count = 4;

  if(argc<3){
     printf("usage: ./sobel imagefile numIterations\n");
     return -1;
  }
  int iterations = atoi(argv[2]);
 
  struct timespec begin, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

  /// Load an image
  src = imread( argv[1] );

  if( !src.data )
    { return -1; }

  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Convert it to gray
  cvtColor( src, src_gray, CV_RGB2GRAY );

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
  #pragma omp parallel num_threads(thread_count)
  for(int i=0; i<iterations; i++){ 
     /// Gradient X
     //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
     Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );   
     convertScaleAbs( grad_x, abs_grad_x );

     /// Gradient Y 
     //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
     Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );   
     convertScaleAbs( grad_y, abs_grad_y );

     /// Total Gradient (approximate)
     addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
  }
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  imshow( window_name, grad );

  waitKey(0);

  //display runtime
  std::cout<<"elapsed time was "<<((end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec - begin.tv_sec)) <<std::endl;

  return 0;
}
