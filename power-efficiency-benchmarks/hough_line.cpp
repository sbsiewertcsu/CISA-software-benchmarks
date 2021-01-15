#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <stdio.h>

#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;

void help()
{
 cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
         "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

int main(int argc, char** argv)
{
 const char* filename = argc >= 2 ? argv[1] : "pic1.jpg";
 struct timespec begin,end; 
 int thread_count=4;
 char key='x';

 if(argc<3){
    printf("usage: ./hough_line imagefile numIterations \n");
    return -1;
 }
 int iterations = atoi(argv[2]);

 Mat src = imread(filename, CV_LOAD_IMAGE_COLOR);
 if(src.empty())
 {
     help();
     cout << "can not open " << filename << endl;
     return -1;
 }

 Mat dst, cdst;
 Canny(src, dst, 50, 200, 3);
 //Canny(src, dst, 120, 240, 3);
 cvtColor(dst, cdst, CV_GRAY2BGR);

  vector<Vec4i> lines;

  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

#pragma omp parallel num_threads(thread_count)
  for(int it=0; it<iterations; it++) { //added by troy might be incorrect placement
  
     //HoughLinesP(dst, lines, 1, CV_PI/180, 50, 100, 10 );
     HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );

     for( size_t i = 0; i < lines.size(); i++ )
     {
       Vec4i l = lines[i];
       //line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
       line( src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
     }
  }
  
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

 // Based on Hough linear transform, we might estimate status to overlay
 putText(src, "Detected Line Overlay", cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(250,250,250), 1, CV_AA);

 //display result for user
 while(key != 'q')
 {
    imshow("source", src);
    key=waitKey();
 }
 imwrite("houghline.png", src);

 key='x';
 while(key != 'q')
 {
     imshow("detected lines", cdst); 
     key=waitKey();
 }
 imwrite("canny.png", cdst);
 
 //display runtime
 std::cout<<"Elapsed time was "<<((end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec - begin.tv_sec)) <<std::endl;

 return 0;
}
