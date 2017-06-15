#include "../include/rasp/imageProcessing/imageStructs.h"
#include "../include/rasp/imageProcessing/saveLoad.h"
#include "../include/rasp/recognition/recognition.h"

#include <highgui.h>
#include <cv.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	Place *places = (Place *) malloc(10*sizeof(Place));
	Place *current;
	int i;

	ImageToLearn currentImages;

	currentImages.image[0] = cvLoadImage("../saveImages/captureAll004_000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[1] = cvLoadImage("../saveImages/captureAll004_001.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[2] = cvLoadImage("../saveImages/captureAll004_002.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[3] = cvLoadImage("../saveImages/captureAll004_003.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[4] = cvLoadImage("../saveImages/captureAll004_004.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	loadPlacesData(places, 10);
	loadImages(places, 10);
	current = &places[4];

	for(i = 0; i < 10; i++)
	{
		winner(places, &places[i], &currentImages, 10);
	}

	//winner(places, current, &currentImages, 10);
}
