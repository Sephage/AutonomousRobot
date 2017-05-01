#include <cv.h>
#include <highgui.h>

#define NB_LANDMARKS_MAX 15

typedef struct {
List *next;
int coord;
}List;

typedef struct {
  float angle;
  IplImage* thumbnail;
}Landmark;

typedef struct {
  Landmark landmarks[NB_LANDMARKS_MAX];
  float movementVectorAngle;
  int landmarksSize;
}Place;
