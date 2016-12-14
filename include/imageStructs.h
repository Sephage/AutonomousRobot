#define NB_LANDMARKS_MAX 15

typedef struct Landmark {
  float angle;
  IplImage* thumbnail;
}*Landmark_p, Landmark_t;

typedef struct Place {
  Landmark_p* landmarks;
  float deplacementVectorAngle;
}*Place_p, Place_t;
