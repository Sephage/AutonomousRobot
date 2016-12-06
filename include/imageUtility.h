/** 
 * \file frameCapture
 * \brief utility file for basic opencv use 
 * \author Paul VALENTIN
 * \date 06/12/2016
 */

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

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

