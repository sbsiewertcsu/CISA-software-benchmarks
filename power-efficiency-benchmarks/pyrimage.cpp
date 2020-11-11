#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <time.h>

using namespace std;
using namespace cv;
const char* window_name = "Pyramids Demo";
int main( int argc, char** argv )
{
    cout << "\n Zoom In-Out demo \n "
            "------------------  \n"
            " * [i] -> Zoom in   \n"
            " * [o] -> Zoom out  \n"
            " * [ESC] -> Close program \n" << endl;
    const char* filename = argc >=2 ? argv[1] : "Cactus-12mpixel.png";
    
    struct timespec begin,end;
    //double start = clock();
    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    
    // Loads an image
    //Mat src = imread( samples::findFile( filename ) ); //problematic line
    Mat src = imread(filename); //troys addition

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default Cactus-12mpixel.png] \n");
        return EXIT_FAILURE;
    }
   // for(;;)
   // {
        imshow( window_name, src );
        //char c = (char)waitKey(0);
        //if( c == 27 )
        //{ break; }
        //else if( c == 'i' )
        //{ 
        //pyrUp( src, src, Size( src.cols*2, src.rows*2 ) );
        //printf( "** Zoom In: Image x 2 \n" );
        //}
        //else if( c == 'o' )
        //{
	for(int i=0; i<2; i++){ 
	  pyrDown( src, src, Size( src.cols/2, src.rows/2 ) );
          printf( "** Zoom Out: Image / 2 \n" );
	}
	
        //}
   // }

    //double end = clock();
    //double elapsed = (end - start)/CLOCKS_PER_SEC; 
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    std::cout<<"elapsed time was "<<((end.tv_nsec - begin.tv_nsec)/1000000000.0 +(end.tv_sec - begin.tv_sec))<<std::endl;
    //std::cout<<"elapsed time was "<<elapsed<<std::endl; 

    return EXIT_SUCCESS;
}
