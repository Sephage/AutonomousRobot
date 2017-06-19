#ifndef RECOGNITION_H
#define RECOGNITION_H

int* multiWinner(Place *places, Place *current, ImageToLearn *currentImages, int placesNbr, int nbWinner);
int winner(Place *places, Place *current, ImageToLearn *currentImages, int placesNbr);
float computeActivities(Place *place, Place *current, ImageToLearn *currentImages, int placeNbr);

#endif
