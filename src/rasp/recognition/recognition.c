#include "../../../include/rasp/imageProcessing/imageUtility.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../../include/rasp/recognition/recognition.h"

#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define __DEBUG

int winner(Place *places, Place *current, ImageToLearn *currentImages, int placesNbr)
{
	int i;
	int index;
	float minimum;
	float activity;

	index = -1;
	minimum = FLT_MAX;
	for(i = 0; i < placesNbr; i++)
	{
		activity = computeActivities(&places[i], current, currentImages, i);

		if(activity < minimum)
		{
			minimum = activity;
			index = i;
		}
	}

	#ifdef __DEBUG
	printf("La place courrante correspond à la place %d\n", index);
	#endif

	return index;
}

float computeActivities(Place *place, Place *current, ImageToLearn *currentImages, int placeNbr)
{
	int i, j;
	int index;
	float minimum;
	float activity;
	float diffAngle;
	float evaluation;

	#ifdef __DEBUG
	int k, l;
	int widthPos;
	int heightPos;
	int placeImNbr;
	int currentImNbr;
	char path[100];
	char path2[100];
	IplImage *debug = 0;
	IplImage *currentImagec = 0;
	#endif

	activity = 0;

	for(i = 0; i < current->landmarksNbr; i++)
	{
		minimum = FLT_MAX;

		for(j = 0; j < place->landmarksNbr; j++)
		{
			diffAngle = (place->landmarks[j]).angle - (current->landmarks[i]).angle;
			diffAngle = diffAngle < -M_PI ? diffAngle + (2 * M_PI) : diffAngle;
			diffAngle = diffAngle > M_PI ? diffAngle - (2 * M_PI) : diffAngle;
			diffAngle = fabs(diffAngle);

			evaluation = diffComparison((current->landmarks[i]).thumbnail, (place->landmarks[j]).thumbnail) * (diffAngle/M_PI);

			if(evaluation < minimum)
			{
				index = j;
				minimum = evaluation;
			}
		}

		#ifdef __DEBUG
		if(index < 4)
			placeImNbr = 0;
		else if(index < 8)
			placeImNbr = 1;
		else if(index < 12)
			placeImNbr = 2;
		else if(index < 16)
			placeImNbr = 3;
		else if(index < 20)
			placeImNbr = 4;

		sprintf(path, "../saveImages/place%.3d_%.3d.jpg", placeNbr, placeImNbr);
		sprintf(path2, "../saveImages/captureAll%.3d_%.3d.jpg", placeNbr, placeImNbr);

		debug = cvLoadImage(path, CV_LOAD_IMAGE_COLOR);
		if(debug == 0)
		{
			debug = cvLoadImage(path2, CV_LOAD_IMAGE_COLOR);
		}



		if(currentImagec == 0)
		{
			currentImagec = cvCreateImage(cvGetSize(currentImages->image[0]), IPL_DEPTH_8U, 3);

			if(i < 4)
				currentImNbr = 0;
			else if(i < 8)
				currentImNbr = 1;
			else if(i < 12)
				currentImNbr = 2;
			else if(i < 16)
				currentImNbr = 3;
			else if(i < 20)
				currentImNbr = 4;

			
			cvCvtColor(currentImages->image[currentImNbr], currentImagec, CV_GRAY2RGB);
		}


		Rgb rgb;

		switch (i)
		{
			case 0:
			rgb.r = 255;
			rgb.g = 255;
			rgb.b = 255;
			break;
			case 1:
			rgb.r = 85;
			rgb.g = 0;
			rgb.b = 0;
			break;
			case 2:
			rgb.r = 170;
			rgb.g = 0;
			rgb.b = 0;
			break;
			case 3:
			rgb.r = 255;
			rgb.g = 0;
			rgb.b = 0;
			break;
			case 4:
			rgb.r = 0;
			rgb.g = 85;
			rgb.b = 0;
			break;
			case 5:
			rgb.r = 0;
			rgb.g = 170;
			rgb.b = 0;
			break;
			case 6:
			rgb.r = 0;
			rgb.g = 255;
			rgb.b = 0;
			break;
			case 7:
			rgb.r = 0;
			rgb.g = 0;
			rgb.b = 85;
			break;
			case 8:
			rgb.r = 0;
			rgb.g = 0;
			rgb.b = 170;
			break;
			case 9:
			rgb.r = 0;
			rgb.g = 0;
			rgb.b = 255;
			break;
			case 10:
			rgb.r = 85;
			rgb.g = 85;
			rgb.b = 0;
			break;
			case 11:
			rgb.r = 170;
			rgb.g = 170;
			rgb.b = 0;
			break;
			case 12:
			rgb.r = 255;
			rgb.g = 255;
			rgb.b = 0;
			break;
			case 13:
			rgb.r = 85;
			rgb.g = 0;
			rgb.b = 85;
			break;
			case 14:
			rgb.r = 170;
			rgb.g = 0;
			rgb.b = 170;
			break;
			case 15:
			rgb.r = 255;
			rgb.g = 0;
			rgb.b = 255;
			break;
			case 16:
			rgb.r = 0;
			rgb.g = 85;
			rgb.b = 85;
			break;
			case 17:
			rgb.r = 0;
			rgb.g = 170;
			rgb.b = 170;
			break;
			case 18:
			rgb.r = 0;
			rgb.g = 255;
			rgb.b = 255;
			break;
			case 19:
			rgb.r = 0;
			rgb.g = 0;
			rgb.b = 0;
			break;
		}



		widthPos = (current->landmarks[i]).index;
		heightPos = 240;

		for(k = heightPos - 64; k < heightPos + 64; k++)
		{
			for(l = widthPos - 32; l < widthPos + 32; l++)
			{
				if(k == heightPos - 64 || l == widthPos - 32 || k == heightPos + 63 || l == widthPos + 31)
				{
					currentImagec->imageData[k*currentImagec->widthStep + l*currentImagec->nChannels] = rgb.b;
					currentImagec->imageData[k*currentImagec->widthStep + l*currentImagec->nChannels+1] = rgb.g;
					currentImagec->imageData[k*currentImagec->widthStep + l*currentImagec->nChannels+2] = rgb.r;
				}
			}
		}

		if((i+1)%4 == 0)
		{
			sprintf(path, "../saveImages/current%.3d_%.3d.jpg", placeNbr, currentImNbr);
			cvSaveImage(path, currentImagec, 0);
			cvReleaseImage(&currentImagec);
			currentImagec = 0;
		}



		widthPos = (place->landmarks[index]).index;

		for(k = heightPos - 64; k < heightPos + 64; k++)
		{
			for(l = widthPos - 32; l < widthPos + 32; l++)
			{
				if(k == heightPos - 64 || l == widthPos - 32 || k == heightPos + 63 || l == widthPos + 31)
				{
					debug->imageData[k*debug->widthStep + l*debug->nChannels] = rgb.b;
					debug->imageData[k*debug->widthStep + l*debug->nChannels+1] = rgb.g;
					debug->imageData[k*debug->widthStep + l*debug->nChannels+2] = rgb.r;
				}
			}
		}

		sprintf(path, "../saveImages/place%.3d_%.3d.jpg", placeNbr, placeImNbr);
		cvSaveImage(path, debug, 0);
		cvReleaseImage(&debug);
		debug = 0;

		printf("L'imagette %d correspond à l'imagette %d\n", i, index);
		#endif

		activity += minimum;
	}

	#ifdef __DEBUG
	printf("L'activité totale est de %lf\n\n", activity);
	#endif

	return activity;
}
