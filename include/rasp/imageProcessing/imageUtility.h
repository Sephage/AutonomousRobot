#ifndef IMAGEUTILITY_H
#define IMAGEUTILITY_H

/** 
 * \file frameCapture
 * \brief utility file for basic opencv use 
 * \author Paul VALENTIN
 * \date 06/12/2016
 */

#include "imageStructs.h"

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/*
 *Capture an image with the camera and return it in gray
 *
 */
IplImage* captureImage();

/*
 *Capture 3 image by turnig servo motor and return the Concatenated image
 *
 */
IplImage* captureAll(int serialD);

/*
 * take an image and fill the array with the sum of columns for each column in the image
 *
 * image : the captured image
 * columnValues : The array to fill 
 * 		HAVE TO BE DECLARED AT THE JUST SIZE
 */
void getSumColumnValues(IplImage* image, int64_t* columnValues);

/*
 * Take an image and print the function columnValues on it
 * image : the image to print the result, only have to have the same width than columnValues
 * columnValues : array that we will print
 *
 * 		width(image) HAVE TO BE EQUAL TO size(ColumnValue)
 */
void printGraphOnImage(IplImage* image, int64_t* columnValues);

/*
 * Take an image and return the thumbnail (32*32) corresponding at the part of the image center in
 * (widthPos;heightPos)
 *
 * image : the image where we will extract thumbnail
 * widthPos : the center of the thumbnail on x axis
 * heightPos : the center of the thumbnail on y axis
 */
IplImage* getThumbnail(IplImage* image, int widthPos, int heightPos);


/*
 * Take an image and save the image in the right place,
 * Put the right information into the saving configuration file.
 *
 * placeNumber : the number of the place that the image belong
 * place : The place we want to save (only thumbnails)
 */
int saveImage(Place* place, int placeNumber);

int saveImages(Place *places, int nbPlace);

void saveNbPlace(int nbPlace);


void savePlacesData(Place* places, int numberPlaces);

int savePlaceData(Place* place, int placeNumber);

void loadPlaceData(Place *place, int nbPlace);

void loadImages(Place *place);
/*
 * Compare two images the current and the learned and
 * return the number of similar pixels
 */
int compareImage(IplImage* current, IplImage* learned);

int diffComparison(IplImage* current, IplImage* learned);

void lowFiltering(int64_t* curve, int64_t* smoothed, int nbrColumn, int size);

void sobel(int64_t* curve, int64_t* derived, int nbrColumn);

Interest *extremumExtract(int64_t *curve, int64_t *derived, int *nbrElt, int nbrColumn, int threshold);

static int compare (void const *a, void const *b);

int learnLocation();

IplImage *compressedThumbnail(IplImage *image, int widthPos, int heightPos);

#endif
