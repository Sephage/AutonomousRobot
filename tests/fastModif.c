#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../include/rasp/imageProcessing/imageUtility.h"
#include "../../include/rasp/imageProcessing/saveLoad.h"

#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <cv.h>

#define PLACESNBR 10

int main(int argc, char **argv)
{
	int i, j;
	char path[100];
	ImageToLearn imagesSet[PLACESNBR];

	for(i = 0; i < PLACESNBR; i++)
	{
		for(j = 0; j < NB_CAPTURE; j++)
		{
			sprintf(path, "../saveImages/captureAll%03d_%03d.jpg", i, j);
			imagesSet[i].image[j] = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);
		}
	}

	
}
