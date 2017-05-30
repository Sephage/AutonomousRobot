#ifndef IMAGESTRUCTS_H
#define IMAGESTRUCTS_H

#include <cv.h>
#include <highgui.h>

#define NB_LANDMARKS_MAX 5
#define SMOOTHNESS 7
#define SLOPE 350

typedef struct {
	int index;
	int value;
}Interest;

typedef struct {
  float angle;
  IplImage* thumbnail;
}Landmark;

typedef struct {
  Landmark landmarks[NB_LANDMARKS_MAX];
  float movementVectorAngle;
  int landmarksSize;
}Place;

#endif
