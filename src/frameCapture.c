#include "../include/frameCapture.h"
#include <stdio.h>


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

	puts("END");
}
