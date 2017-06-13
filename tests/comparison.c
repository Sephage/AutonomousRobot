#include "../include/rasp/imageProcessing/imageStructs.h"
#include "../include/rasp/imageProcessing/saveLoad.h"
#include "../include/rasp/recognition/recognition.h"

#include <highgui.h>
#include <cv.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	Place *places = (Place *) malloc(6*sizeof(Place));
	Place *current;

	ImageToLearn currentImages;

	currentImages.image[0] = cvLoadImage("../saveImages/captureAll003_000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[1] = cvLoadImage("../saveImages/captureAll003_001.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[2] = cvLoadImage("../saveImages/captureAll003_002.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[3] = cvLoadImage("../saveImages/captureAll003_003.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	currentImages.image[4] = cvLoadImage("../saveImages/captureAll003_004.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	loadPlacesData(places, 6);
	current = &places[3];

	loadImages(places, 6);	

	winner(places, current, &currentImages, 6);
}
