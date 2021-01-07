#include "iostream"

//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgcodecs/imgcodecs.hpp"

//#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

#include <time.h>
#include <omp.h>

using namespace std;
using namespace cv;
const char* window_name = "Pyramids Demo";
int main( int argc, char** argv )
{
    int thread_count = 4;
    if(argc<3){
       printf("usage: ./pyrimage imagefile numIterations \n");
       return -1;
    }
    int iterations = atoi(argv[2]);
    const char* filename = argc >=2 ? argv[1] : "Cactus-120kpixel.png";
    printf("filename is %s\n", filename); 

    struct timespec begin,end; 
    
    // Loads an image
    //Mat src = imread( samples::findFile( filename ) ); //problematic line
    Mat src = imread(filename); //troys addition
    Mat newImage;

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default Cactus-120kpixel.png] \n");
        return EXIT_FAILURE;
    }

    //time the transformation
    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    #pragma omp parallel num_threads(thread_count) 
    for(int i=0; i<iterations; i++){
       pyrUp(src,newImage, Size(src.cols*2, src.rows*2));
       //pyrUp (src, src, Size( src.cols*2, src.rows*2) );  //zoom in
       //pyrDown( src, src, Size( src.cols/2, src.rows/2 ) );  //zoom out
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    //display the runtime
    std::cout<<"elapsed time was "<<((end.tv_nsec - begin.tv_nsec)/1000000000.0 +(end.tv_sec - begin.tv_sec))<<std::endl;
   
    //display result 
    //imshow( window_name, src);
    //waitKey(0);

    //for parallel version to verify it works
    imshow(window_name, newImage);
    waitKey(0);

    return EXIT_SUCCESS;
}
