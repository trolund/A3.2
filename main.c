#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
#include "highgui.h"
#include <stdio.h>

int main( int argc, char** argv )
{

    printf("Arguments were passed to main():\n");
    for (int i = 0; i<argc; i++)
        printf("argv[%d] = %s \n", i, argv[i]);
    printf("\n");

    if( argc != 2)
    {
        printf( "Unable to load the image\n"
                        "Pass it as the first parameter, e.g.: test.jpg?????\n" );
        return -1;
    }

    IplImage* image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);  // Loads an image from a file.


    IplImage* destination = cvCreateImage(cvSize( image->width, image->height ), IPL_DEPTH_8U, 1 );

    cvCvtColor(image, destination, CV_RGB2GRAY );

    printf("img dim: %d*%d \n\n",destination->width, destination->height );

    cvCvtColor(image, destination, CV_RGB2GRAY );

    static int intensitys[256];

    for(int x = 0; x < destination->width; x++) {
        for (int y = 0; y < destination->height; ++y) {

            unsigned char intensity = CV_IMAGE_ELEM(destination, uchar, y, x);
            int in = intensity;

          //  printf("intensity: %d, x: %d, y: %d \n",in,x,y);

            intensitys[in]++;
        }
    }

    FILE *fp = fopen("HISTOGRAM.SOL", "w+");

    fclose(fp);

    int sum = 0;
    int numberOfDifferentIntensities = 0;

    for (int j = 0; j <= 255; ++j) {
        if(intensitys[j] != 0) {
            printf("%d : %d \n", j, intensitys[j]);
            numberOfDifferentIntensities++;
        }

        sum += intensitys[j];
    }

    printf("sum: %d", sum);

    FILE *fpA = fopen("HISTOGRAM.SOL", "a+");

    fprintf(fpA, "%s \n", "HISTOGRAM.SOL" );

    fprintf(fpA, "%d \n", numberOfDifferentIntensities);

    fprintf(fpA, "%dx%d \n", destination->width, destination->height);




    for (int f = 0; f <= 255; ++f) {
        fprintf(fp,"%d %d \n", f, intensitys[f]);
    }

    fclose(fpA);

    if(image== NULL)// Check for invalid input
    {
        printf("Could not open or find the image\n") ;
        return -1;
    }


    /* display image in window */
    cvNamedWindow("MyWindow_Name",CV_WINDOW_AUTOSIZE); // Create a window for display.
    cvShowImage("MyWindow_Name",destination); // Show our image inside window.

    /*int param[2];
    param[0] = CV_IMWRITE_JPEG_QUALITY;
    param[1] = 95;*/
    cvSaveImage("tmp_typewriter.jpg", image, 0);  // Saves an image to a specified file.

    cvWaitKey(0);    // Wait for a keystroke in the window

    cvReleaseImage(&image); // release memory.
    cvDestroyWindow("MyWindow_Name"); //destroy windows

    return 0;
}

void writeFile(){





}