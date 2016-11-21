/** 
 * \file frameCapture
 * \brief utility file for basic opencv use 
 * \author Paul VALENTIN
 * \date 17/11/2016
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
