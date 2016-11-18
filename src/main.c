/* Possibilité de faire un fichier header */
#include "../include/frameCapture.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main(int* argv, char** argc){
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* image = 0;
	int64_t* columnDatas;
	int16_t i;
	char* name = "What an awesome image";

	puts("Initialization ...");
	
	//if(!captureFrame(image, capture)) exit(1);
	image = cvQueryFrame(capture);
	if(!image){
		puts("Image fail to load");
		exit(1);
	}
	columnDatas = malloc(image->width * sizeof(int64_t));

	puts("Initialization complete !!");

	puts("Data of the image :");
	printf("image->height = %i\n", image->height);
	printf("image->width = %i\n", image->width);
	printf("image->nChannels = %i\n", image->nChannels);

	getSumColumnValues(image, columnDatas);

	for(i=0 ; i<image->height ; i++){
		printf("%li ", columnDatas[i]);
	}
	puts("");

	cvNamedWindow(name, CV_WINDOW_AUTOSIZE);

	cvShowImage(name, image);
	
	while(cvWaitKey(30) == -1);
	cvReleaseImage(&image);
	free(columnDatas);

	return 0;
}
