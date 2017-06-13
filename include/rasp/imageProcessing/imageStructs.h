#ifndef IMAGESTRUCTS_H
#define IMAGESTRUCTS_H

#include <cv.h>
#include <highgui.h>

#define NB_LANDMARKS_MAX 20
#define NB_LANDMARKS_IND 4
#define SMOOTHNESS 7
#define SLOPE 350
#define CAMERA_VISION_ANGLE 51.6
#define CAMERA_ROTATION 45
#define ANGLES_CAPTURE {175,130,85,45,0}
#define NB_CAPTURE 5

typedef struct{
	int r;
	int g;
	int b;
}Rgb;

typedef struct{
	IplImage* image[NB_CAPTURE];
}ImageToLearn;

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
