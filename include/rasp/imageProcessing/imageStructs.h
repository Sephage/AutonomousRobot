#ifndef IMAGESTRUCTS_H
#define IMAGESTRUCTS_H

#include <cv.h>
#include <highgui.h>

#define NB_LANDMARKS_MAX 15
#define SMOOTHNESS 7
#define SLOPE 350
#define CAMERA_VISION_ANGLE 51.6
#define IMAGE_VISION_ANGLE 151.6

typedef struct {
	int index;
	int value;
}Interest;

typedef struct {
  int index;
  float angle;
  IplImage *thumbnail;
}Landmark;

typedef struct {
  Landmark landmarks[NB_LANDMARKS_MAX];
  float movementVectorAngle;
  int landmarksNbr;
}Place;

#endif
