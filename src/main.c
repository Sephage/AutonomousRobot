/* Possibilité de faire un fichier header */
#include "../include/imageUtility.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#define __DEBUG 0

int main(int* argv, char** argc){
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* image = 0;
	IplImage* canny = 0;
	IplImage* gray = 0;
	IplImage* graph = 0;
	IplImage* thumbnail = 0;
	IplImage* thumbnail2 = 0;
	int64_t* columnDatas;
	int16_t i;
	char* name = "What an awesome pic";
	char* graphName = "What an awesome graph";

	puts("Initialization ...");
	
	image = cvQueryFrame(capture);
	graph = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	cvSet(image, CV_RGB(255,255,255), NULL);
	//canny = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	if(!image){
		puts("Image fail to load");
		exit(1);
	}
	columnDatas = malloc(image->width * sizeof(int64_t));
	cvNamedWindow(name, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(graphName, CV_WINDOW_AUTOSIZE);

	puts("Initialization complete !!");

	puts("Data of the image :");
	printf("image->height = %i\n", image->height);
	printf("image->width = %i\n", image->width);
	printf("image->nChannels = %i\n", image->nChannels);

	image = cvQueryFrame(capture);
	if(!image){
		puts("Image fail to load");
		exit(1);
	}
	cvCvtColor(image, gray, CV_RGB2GRAY);
	//cvCanny( image, canny, 70, 100, 3);
	getSumColumnValues(gray, columnDatas);
	if(__DEBUG ){
		for(i=0 ; i<image->height ; i++){
			printf("%li ", columnDatas[i]);
		}
		puts("");
	}

	printGraphOnImage(graph, columnDatas);
	printGraphOnImage(gray, columnDatas);

	thumbnail = getThumbnail(image, 50, 30);
	

	image = cvQueryFrame(capture);
	thumbnail2 = getThumbnail(image, 50, 30);

	int recog = compareImage(thumbnail, thumbnail2);
	printf("Image reconnu a : %d pourcent \n", recog);

	//Save
	cvSaveImage("../saveImages/imgTest.jpg", image, 0);
	cvSaveImage("../saveImages/graphTest.jpg", graph, 0);
	cvShowImage(graphName, graph);
	cvShowImage(name, gray);

	saveImage(thumbnail, 1, 30);
	while(cvWaitKey(30) == -1){
	}

	cvReleaseCapture(&capture);
	cvReleaseImage(&image);
	//cvReleaseImage(&canny);
	cvReleaseImage(&gray);
	free(columnDatas);

	return 0;
}
