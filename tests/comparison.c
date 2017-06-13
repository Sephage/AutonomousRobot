#include "../include/rasp/imageProcessing/imageStructs.h"
#include "../include/rasp/recognition/recognition.h"

#include <highgui.h>
#include <cv.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	Place *places = (Place *) malloc(3*sizeof(Place));
	char path[100];
	Place current;
	int i,j;



	places[0].landmarksNbr = 5;
	current.landmarksNbr = 5;
	for(i = 0; i < 5; i++)
	{
		sprintf(path, "../saveImages/%d_%d.jpg", i);

		places[0].landmarks[i].thumbnail = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);
		current.landmarks[i].thumbnail = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);

		places[0].landmarks[i].angle = 0.25*i;
		current.landmarks[i].angle = 0.25*i;
	}

	places[1].landmarksNbr = 5;
	for(i = 0; i < 5; i++)
	{
		sprintf(path, "../saveImages/place02/thumbnails/thumbnails%.3d.jpg", i);

		places[1].landmarks[i].thumbnail = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);

		places[1].landmarks[i].angle = 0.5*i;
	}

	places[2].landmarksNbr = 5;
	for(i = 0; i < 5; i++)
	{
		sprintf(path, "../saveImages/place03/thumbnails/thumbnails%.3d.jpg", i);

		places[2].landmarks[i].thumbnail = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);

		places[2].landmarks[i].angle = 0.5*i;
	}

	winner(places, &current, 3);
}
