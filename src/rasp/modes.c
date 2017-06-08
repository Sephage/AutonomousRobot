#include "../../include/rasp/modes.h"

void learning(char* dirPath, int deplAngle, int serialD) {
  IplImage *image;

  image = captureAll(serialD);
//  learnLocation(image, serialD, deplAngle);
//  savePlaceData(dirPath, angle, landmarksNbr);
}

void autonomous(int serialD, Server server) {
//  Place places[] = LoadPlaces();
  IplImage *image;
  int cont = 1, placeIndex, angle;

  while(cont) {
    image = captureAll();
    //imageTreatment(image);

    //placeIndex = recognition(image);
    //angle = places[placeIndex].depl;
  }

}
