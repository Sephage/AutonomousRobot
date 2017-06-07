#include "../../../include/rasp/imageProcessing/imageUtility.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../../include/serial/Serial.h"

#include <stdio.h>

/*For saving functions*/
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

#define __DEBUG

IplImage* concatenateImage(IplImage* image1, IplImage* image2, IplImage* image3) {

	int i, j, k;
	IplImage* result = cvCreateImage(cvSize(image1->width*3, image1->height), IPL_DEPTH_8U, 1);
	int width = image1->width;
	int height = image1->height;
	int nChannels = image1->nChannels;
	int step = image1->widthStep;
	int bigstep = result->widthStep;

	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			for(k = 0; k < nChannels; k++) {
				result->imageData[i*bigstep + j*nChannels + k] = image1->imageData[i*step + j*nChannels + k];
				result->imageData[i*bigstep + (j+width)*nChannels + k] = image2->imageData[i*step + j*nChannels + k];
				result->imageData[i*bigstep + (j+(width*2))*nChannels + k] = image3->imageData[i*step + j*nChannels + k];
			}
		}
	}

	return result;
}

IplImage* captureImage(){
	IplImage *image = 0;
 	IplImage *gray = 0;
 	CvCapture *capture;

 	capture = cvCaptureFromCAM(0);
 	image = cvQueryFrame(capture);
 	if(!image)
 	{
 		puts("Image fail to load");
 	}

 	gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
 	cvCvtColor(image, gray, CV_RGB2GRAY);

	cvReleaseImage(&image);
	cvReleaseCapture(&capture);

	 return gray;
}

IplImage* captureAll(int serialD){
 	IplImage *gray1 = 0, *gray2 = 0, *gray3 = 0, *result = 0;
	char* bufferSerial = (char*)malloc(4 * sizeof(char));

	turnServo(serialD, 85, bufferSerial);
	sleep(1);
	gray2 = captureImage();
	sleep(1);
	cvSaveImage("../saveImages/cap2.jpg", gray2, 0);

	turnServo(serialD, 0, bufferSerial);
	sleep(1);
	gray1 = captureImage();
	sleep(1);
	cvSaveImage("../saveImages/cap1.jpg", gray1, 0);

	turnServo(serialD, 175, bufferSerial);
	sleep(1);
	gray3 = captureImage();
	sleep(1);
	cvSaveImage("../saveImages/cap3.jpg", gray3, 0);

	turnServo(serialD, 85, bufferSerial);

	//Concatenate all 3 image in result
	result = concatenateImage(gray1, gray2, gray3);
	cvSaveImage("../saveImages/conca.jpg", result, 0);

	 return result;
}

void sobel(int64_t *curve, int64_t *derived, int nbrColumn)
{
	int i;
	if(derived == NULL)
	{
		fputs("NULL pointer exception in sobel",stderr);
		return ;
	}

	//Calcul du premier élément en créant une redondance de l'information
	derived[0] = -curve[0]+curve[1];

	for(i=1;i<nbrColumn-1;i++)
	{
		derived[i] = -curve[i-1]+curve[i+1];
	}

	//Calcul du dernier élément en créant une redondance de l'information
	derived[i+1] = -curve[i]+curve[i+1];
}

void lowFiltering(int64_t *curve, int64_t *smoothed, int nbrColumn, int size)
{
	int mean;
	int i, j;
	int iLeft, iRight;

	if(smoothed == NULL)
	{
		fputs("NULL pointer exception in lowFiltering",stderr);
		return ;
	}

	for(i = 0; i < nbrColumn; i++)
	{
		//On détermine les bornes à prendre en compte pour le filtre
		mean = 0;
		iLeft = i-size/2 >= 0 ? i-size/2 : 0;
		iRight = i+size/2 < nbrColumn ? i+size/2 : nbrColumn-1;

		for(j = iLeft; j <= iRight; j++)
		{
			mean += curve[j];
		}
		smoothed[i]=mean/(iRight-iLeft+1);
	}
}

Interest *extremumExtract(int64_t *curve, int64_t *derived, int *nbrElt, int nbrColumn, int threshold)
{
	int i, p;
	int *locations;
	Interest *extremums;


	p = 0;
	locations = (int *) malloc(nbrColumn*sizeof(int));

	for(i = 0; i < nbrColumn; i++)
	{
		locations[i] = -1;
	}


	for(i = 32; i < nbrColumn-33; i++)
	{
		if(derived[i]*derived[i+1] < 0)
		{
			if(abs(derived[i+1]-derived[i]) > threshold)
			{
				locations[p] = i;

				p++;
			}
		}
	}

	extremums = malloc(p*sizeof(Interest));
	*nbrElt = p;

	while(--p >= 0)
	{
		extremums[p].index = locations[p];
		extremums[p].value = abs(derived[locations[i]+1]-derived[locations[i]]);
		//extremums[p].value = curve[p];
	}

	free(locations);

	return extremums;
}

static int compare (void const *a, void const *b)
{
   Interest const *pa = a;
   Interest const *pb = b;

   return pa->value - pb->value;
}

IplImage *compressedThumbnail(IplImage *image, int widthPos, int heightPos)
{
	int i, j;
	IplImage *thumbnail = 0;
	int thumbnailPos, imagePos;

	if(widthPos < 32 || widthPos >= image->width-32)
	{
		fputs("This position is not permitted in compressedThumbnail\n",stderr);
		return NULL;
	}

	thumbnail = cvCreateImage(cvSize(32, 32), IPL_DEPTH_8U, 1);
	if(thumbnail == 0)
	{
		fputs("Allocation failed in compressedThumbnail\n",stderr);
		return NULL;
	}

	for(i = 0; i < 32; i++)
	{
		for(j = 0; j < 32; j++)
		{
			thumbnailPos = i * thumbnail->widthStep + j;
			imagePos = (4 * i + heightPos - 64) * image->widthStep + (2 * j + widthPos - 32);
			thumbnail->imageData[thumbnailPos]=image->imageData[imagePos];
		}
	}

	return thumbnail;
}

void getSumColumnValues(IplImage* image, int64_t* columnValues)
{
	int32_t i,j,k;
	if(columnValues == NULL)
	{
		fputs("The array in getSumColumnValues is NULL",stderr);
		return ;
	}

	for(i=0 ; i<image->width ; i++)
	{
		columnValues[i] = 0;
		for(j=0 ; j<image->height ; j++)
		{
			for(k=0 ; k<image->nChannels ; k++)
			{
				columnValues[i]	+= (uchar)image->imageData[j*image->widthStep+i*image->nChannels+k];
			}
		}
	}
}

void printGraphOnImage(IplImage* image, int64_t* columnValues)
{
	int i,k;
	int height = image->height;
	int width = image->width;
	int step = image->widthStep;
	int nChannels = image->nChannels;
	uchar *data = (uchar *)image->imageData;
	printf("step = %d, nCHannels = %d\n", step, nChannels);
	if(columnValues == NULL)
	{
		fputs(" in printGraphOnImage array not malloc\n", stderr);
		return;
	}
	for(i=0 ; i<width ; i++)
	{
		for(k=0 ; k<nChannels ; k++)
		{
			data[((((columnValues[i]/(255*nChannels))*-1)+height)*step) + i*nChannels + k] =
				255/*-data[(columnValues[i]/(255*nChannels))*step + i*nChannels + k]*/;
		}
	}
}

IplImage* getThumbnail(IplImage* image, int widthPos, int heightPos)
{
	IplImage* thumbnail = 0;

	cvSetImageROI(image, cvRect(widthPos, heightPos, 32, 32));
	thumbnail = cvCreateImage(cvSize(32, 32), image->depth, image->nChannels);
	cvCopy(image, thumbnail, NULL);
	cvResetImageROI(image);

	return thumbnail;
}

/*To rewrite : only save images*/
int saveImage(IplImage* imageToSave, int placeNumber, float angle)
{
	DIR* directory = 0;
	struct dirent* file = 0;
	int exist = 0;
	char placeName[256];
	char imageName[256];
	struct stat st = {0};
	FILE* configFile = 0;
	char configName[256];

	sprintf(placeName, "../saveImages/%d", placeNumber);
	/*regarder si le dossier de la place exist si oui on regarde dedans et enregistre la place a nb+1 sinon on créé et on enregistre a 1*/
	if(stat(placeName, &st) == -1)
	{
		printf("Creation du fichier\n");
		mkdir(placeName, 0777);
		cvSaveImage("../saveImages/1/1.jpg", imageToSave, 0);
		/* Ecrire dans le fichier de config : number angle*/
		sprintf(configName, "../saveImages/1/config.cfg");
		configFile = fopen(configName, "a+");
		fprintf(configFile,"1 %lf", angle);
	}
}

int compareImage(IplImage* current, IplImage* learned)
{
	const int range = 3;
	int width = current->width;
	int height = current->height;
	int step = current->widthStep;
	int nChannels = current->nChannels;
	int i,j,k;
	int recognition = 0;

	if(width != learned->width)
	{
		fputs("Widh aren't similar\n", stderr);
		return -1;
	}
	if(height != learned->height)
	{
		fputs("Height aren't similar\n", stderr);
		return -1;
	}
	if(step != learned->widthStep)
	{
		fputs("step aren't similar\n", stderr);
		return -1;
	}
	if(nChannels != learned->nChannels)
	{
		fputs("nChannels aren't similar\n", stderr);
		return -1;
	}
	for(i=0 ; i<height ; i++)
	{
		for(j=0 ; j<width ; j++)
		{
			for(k=0 ; k<nChannels ; k++)
			{
				/*Faut tester pour voir combien de delta on laisse pour la reconnaissance*/
				if(current->imageData[i*step+j*nChannels+k] > learned->imageData[i*step+j*nChannels+k]-range
				&& current->imageData[i*step+j*nChannels+k]<learned->imageData[i*step+j*nChannels+k]+range)
				{
					recognition += 1;
				}
			}
		}
	}
	recognition = (100*recognition)/(height*width*nChannels);
	return recognition;
}

int diffComparison(IplImage* current, IplImage* learned){
	int width = current->width;
	int height = current->height;
	int step = current->widthStep;
	int nChannels = current->nChannels;
	int i,j,k;
	int diff = 0;

	if(width != learned->width)
	{
		fputs("Widh aren't similar\n", stderr);
		return -1;
	}
	if(height != learned->height)
	{
		fputs("Height aren't similar\n", stderr);
		return -1;
	}
	if(step != learned->widthStep)
	{
		fputs("step aren't similar\n", stderr);
		return -1;
	}
	if(nChannels != learned->nChannels)
	{
		fputs("nChannels aren't similar\n", stderr);
		return -1;
	}
	for(i=0 ; i<height ; i++)
	{
		for(j=0 ; j<width ; j++)
		{
			for(k=0 ; k<nChannels ; k++)
			{
				diff += abs(learned->imageData[i*step+j*nChannels+k] - current->imageData[i*step+j*nChannels+k]);
			}
		}
	}
	return diff;
}

int learnLocation()
{
	IplImage *thumbnail = 0;
	Interest *extremums;
	IplImage *image = 0;
	IplImage *gray = 0;
	CvCapture *capture;
	int64_t *sumColumn;
	int64_t *smoothed;
	int64_t *derived;
	int nbrLandmarks;
	char path[100];
	int nbrElt;
	int i;



	nbrLandmarks = 0;

	capture = cvCaptureFromCAM(0);
	image = cvQueryFrame(capture);
	if(!image)
	{
		puts("Image fail to load");
		exit(1);
	}

	gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
	cvCvtColor(image, gray, CV_RGB2GRAY);

	sumColumn = malloc(image->width * sizeof(int64_t));
	smoothed = malloc(image->width * sizeof(int64_t));
	derived = malloc(image->width * sizeof(int64_t));



	getSumColumnValues(gray, sumColumn);
	lowFiltering(sumColumn, smoothed, image->width, SMOOTHNESS);
	sobel(smoothed, derived, image->width);
	extremums = extremumExtract(sumColumn, derived, &nbrElt, image->width, SLOPE);
	qsort((void *) extremums, nbrElt, sizeof(Interest), compare);

	#ifdef __DEBUG
	IplImage *graph = 0;
	graph = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	printGraphOnImage(graph, smoothed);
	cvSaveImage("../saveImages/smoothed.jpg", graph, 0);
	cvReleaseImage(&graph);
	#endif



	mkdir("../saveImages/thumbnails", 0777);
	for(i  = 0; i < NB_LANDMARKS_MAX && i < nbrElt; i++)
	{
		sprintf(path, "../saveImages/thumbnails/thumbnails%.3d.jpg", i);

		thumbnail = compressedThumbnail(gray, extremums[i].index, 240);
		cvSaveImage(path, thumbnail, 0);
		cvReleaseImage(&thumbnail);

		nbrLandmarks++;
	}

	cvSaveImage("../saveImages/image.jpg", image, 0);



	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	free(sumColumn);
	free(smoothed);
	free(derived);

	return nbrLandmarks;
}
