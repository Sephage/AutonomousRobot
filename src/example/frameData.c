#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char *argv[])
{
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* img = 0; 
	int height,width,step,channels;
	uchar *data;
	int i,j,k;

	/*if(argc<2){
		printf("Usage: main <image-file-name>\n\7");
		exit(0);
	}*/

	// load an image  
	//img=cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	for(;;){
		img = cvQueryFrame( capture );
		if(!img){
			printf("Could not load image file: %s\n",argv[1]);
			exit(0);
		}

		// get the image data
		height    = img->height;
		width     = img->width;
		step      = img->widthStep;
		channels  = img->nChannels;
		data      = (uchar *)img->imageData;
		//printf("Processing a %dx%d image with %d channels\n",height,width,channels); 

		// create a window
		cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
		cvMoveWindow("mainWin", 600, 300);

		// invert the image
		for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
			data[i*step+j*channels+k]=255-data[i*step+j*channels+k];

		// show the image
		cvShowImage("mainWin", img );

		// wait for a key
		if (cvWaitKey(30) != -1 ) break;
	}

	// release the image
	cvReleaseImage(&img );
	return 0;
}
