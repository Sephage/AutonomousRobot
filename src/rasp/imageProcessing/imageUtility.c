#include "../../../include/rasp/imageProcessing/imageUtility.h"

#include <stdio.h>

/*For saving functions*/
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <errno.h>

void contourDetection(int64_t* interest, int64_t* columnData,int16_t nbrColumn)
{
	int32_t i;
	if(interest == NULL)
	{
		fputs("The array in contourDetection is NULL",stderr);
		return ;
	}

	//Calcul du premier élément en créant une redondance de l'information
	interest[0] = abs(-columnData[0]+columnData[1]);

	for(i=1;i<nbrColumn-1;i++)
	{
		interest[i] = abs(-columnData[i-1]+columnData[i+1]);
	}

	//Calcul du dernier élément en créant une redondance de l'information
	interest[i+1] = abs(-columnData[i]+columnData[i+1]);
}

void smoothingGraph(int64_t* columnData, int64_t* smoothColumnData, int16_t nbrColumn)
{
	int32_t i;
	if(smoothColumnData == NULL)
	{
		fputs("The array in smoothingGraph is NULL",stderr);
		return ;
	}

	//Calcul du premier élément
	smoothColumnData[0]=(2*columnData[0]+columnData[1])/3;

	for(i=1;i<nbrColumn-1;i++)
	{
		smoothColumnData[i]=(columnData[i-1]+columnData[i]+columnData[i+1])/3;
	}

	//Calcul du dernier élément
	smoothColumnData[i+1]=(columnData[i]+2*columnData[i+1])/3;
}

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

/*To rewrite : only save images*/
int saveImage(IplImage* imageToSave, int placeNumber, float angle){
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
	if(stat(placeName, &st) == -1){
		printf("Creation du fichier\n");
		mkdir(placeName, 0777);
		cvSaveImage("../saveImages/1/1.jpg", imageToSave, 0);
		/* Ecrire dans le fichier de config : number angle*/
		sprintf(configName, "../saveImages/1/config.cfg");
		configFile = fopen(configName, "a+");
		fprintf(configFile,"1 %lf", angle);
	}
	else{

	}


}

int compareImage(IplImage* current, IplImage* learned){
	const int range = 3;
	int width = current->width;
	int height = current->height;
	int step = current->widthStep;
	int nChannels = current->nChannels;
	int i,j,k;
	int recognition = 0;

	if(width != learned->width){
		fputs("Widh aren't similar\n", stderr);
		return -1;
	}
	if(height != learned->height){
		fputs("Height aren't similar\n", stderr);
		return -1;
	}
	if(step != learned->widthStep){
		fputs("step aren't similar\n", stderr);
		return -1;
	}
	if(nChannels != learned->nChannels){
		fputs("nChannels aren't similar\n", stderr);
		return -1;
	}
	for(i=0 ; i<height ; i++){
		for(j=0 ; j<width ; j++){
			for(k=0 ; k<nChannels ; k++){
				/*Faut tester pour voir combien de delta on laisse pour la reconnaissance*/
				if(current->imageData[i*step+j*nChannels+k] > learned->imageData[i*step+j*nChannels+k]-range
				&& current->imageData[i*step+j*nChannels+k]<learned->imageData[i*step+j*nChannels+k]+range){
					recognition += 1;
				}
			}
		}
	}
	recognition = (100*recognition)/(height*width*nChannels);
	return recognition;
}
