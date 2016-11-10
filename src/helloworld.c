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

	IplImage* img = cvCreateImage(cvSize(300,300), frame->depth, frame->nChannels);
	IplImage* gray_out = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U,1);
	IplImage* canny_out = cvCreateImage( cvGetSize(img), IPL_DEPTH_8U,1);
	int i=0;
	for(;;){
		frame = cvQueryFrame( capture );
		cvResize(frame,img,CV_INTER_AREA);
		cvCvtColor(img , gray_out, CV_RGB2GRAY);
		cvCanny( gray_out, canny_out, 70, 100, 3 );

		if(i < 10)
			cvShowImage(window_title, img);
		else if(i < 20)
			cvShowImage(window_title, gray_out);
		else{
			cvShowImage(window_title, canny_out);
			if(i ==30)
				i = 0;
		}
		if(cvWaitKey(30) != -1) break;
		i++;

	}

	cvReleaseCapture( &capture );
	cvDestroyWindow(window_title);
	return 0;
}
