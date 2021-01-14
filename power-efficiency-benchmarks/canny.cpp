#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace cv;
using namespace std;

// Global variables
Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char window_name[] = "Edge Map";


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur(src_gray, detected_edges, Size(3,3));

  /// Canny detector
  Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

  /// Using Canny's output as a mask, we display our result with image color
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
 }


/** @function main */
int main( int argc, char** argv )
{
  struct timespec begin, end;
  int iterations=1, idx;
  int thread_count=4;

  if(argc < 3) 
  { 
    cout << "usage: canny imagefile iterations" << endl; return -1;
  } else
  {
    iterations = atoi(argv[2]);
  }

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Load an image
  src = imread( argv[1] );

  if( !src.data ) { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );


  // Timed benchmark - per POSIX thread, using affinity and SCHED_FIFO
  //
  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

#pragma omp parallel num_threads(thread_count)
  for(idx=0; idx < iterations; idx++)
  {
    cvtColor(src, src_gray, CV_BGR2GRAY);
    CannyThreshold(0, 0);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  //
  // End timed section

  cout<<"elapsed time was "<<((end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec - begin.tv_sec)) <<endl;

  // Benchmark output approval - wait until user exit program by pressing a key
  imshow(window_name, dst);

  waitKey(0);



  return 0;
}
