#include "../include/imageUtility.h"

#include <stdio.h>

/*For saving functions*/
#include <sys/types.h>
#include <dirent.h>

#include <errno.h>


void getSumColumnValues(IplImage* image, int64_t* columnValues){
	int32_t i,j,k;
	if(columnValues == NULL){
		fputs("The array in getSumColumnValues is NULL",stderr);
		return ;
	}

	for(i=0 ; i<image->width ; i++){
		columnValues[i] = 0;
		for(j=0 ; j<image->height ; j++){
			for(k=0 ; k<image->nChannels ; k++){
				columnValues[i]	+= (uchar)image->imageData[j*image->widthStep+i*image->nChannels+k];
			}
		}
	}
}

void printGraphOnImage(IplImage* image, int64_t* columnValues){
	int i,k;
	int height = image->height;
	int width = image->width;
	int step = image->widthStep;
	int nChannels = image->nChannels;
	uchar *data = (uchar *)image->imageData;
	printf("step = %d, nCHannels = %d\n", step, nChannels);
	if(columnValues == NULL){
		fputs(" in printGraphOnImage array not malloc\n", stderr);
		return;
	}
	for(i=0 ; i<width ; i++){
		for(k=0 ; k<nChannels ; k++){
			data[((((columnValues[i]/(255*nChannels))*-1)+height)*step) + i*nChannels + k] = 
				255-data[(columnValues[i]/(255*nChannels))*step + i*nChannels + k];
		}
	}
}

IplImage* getThumbnail(IplImage* image, int widthPos, int heightPos){
	IplImage* thumbnail = 0;

	cvSetImageROI(image, cvRect(widthPos, heightPos, 32, 32));
	thumbnail = cvCreateImage(cvSize(32, 32), image->depth, image->nChannels);
	cvCopy(image, thumbnail, NULL);
	cvResetImageROI(image);

	return thumbnail;
}

void saveImage(IplImage* imageToSave, int placeNumber, float angle){
	DIR* directory = 0;	

	directory = opendir("../saveImages");
	/*regarder si le dossier de la place exist si oui on regarde dedans et enregistre la place a nb+1 sinon on créé et on enregistre a 1*/


}
