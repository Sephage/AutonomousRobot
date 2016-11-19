/* Possibilité de faire un fichier header */
#include "../include/frameCapture.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main(int* argv, char** argc){
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* image = 0;
	IplImage* canny = 0;
	IplImage* gray = 0;
	int64_t* columnDatas;
	int16_t i;
	char* name = "What an awesome pic";

	puts("Initialization ...");
	
	//if(!captureFrame(image, capture)) exit(1);
	image = cvQueryFrame(capture);
	canny = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	if(!image){
		puts("Image fail to load");
		exit(1);
	}
	columnDatas = malloc(image->width * sizeof(int64_t));
	cvNamedWindow(name, CV_WINDOW_AUTOSIZE);

	puts("Initialization complete !!");

	puts("Data of the image :");
	printf("image->height = %i\n", image->height);
	printf("image->width = %i\n", image->width);
	printf("image->nChannels = %i\n", image->nChannels);

	while(cvWaitKey(30) == -1){
		image = cvQueryFrame(capture);
		if(!image){
			puts("Image fail to load");
			exit(1);
		}
		cvCvtColor(image, gray, CV_RGB2GRAY);
		cvCanny( image, canny, 70, 100, 3);
		getSumColumnValues(canny, columnDatas);

		for(i=0 ; i<image->height ; i++){
			printf("%li ", columnDatas[i]);
		}
		puts("");


		cvShowImage(name, canny);
	}

	cvReleaseCapture(&capture);
	cvReleaseImage(&image);
	cvReleaseImage(&canny);
	cvReleaseImage(&gray);
	free(columnDatas);

	return 0;
}
