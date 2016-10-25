#include <stdio.h>

#include <stdlib.h>

#include <opencv/highgui.h>

#include <opencv/cv.h>

int main (int argc, char* argv[])
{

	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* frame;

	const char* window_title = "Hello, OpenCV!";


	frame = cvQueryFrame( capture );
	cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);

	IplImage* img = cvCreateImage(cvSize(150,150), frame->depth, frame->nChannels);
	IplImage* gray_out = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U,1);
	IplImage* canny_out = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U,1);

	for(;;){
		frame = cvQueryFrame( capture );
		cvResize(frame,img,CV_INTER_AREA);
		cvCvtColor(img , gray_out, CV_RGB2GRAY);
		cvCanny( gray_out, canny_out, 70, 100, 3 );

		cvShowImage(window_title, gray_out);
		if(cvWaitKey(30) != -1) break;

	}

	cvReleaseCapture( &capture );
	cvDestroyWindow(window_title);
	return 0;
}
