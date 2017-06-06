#include "../../include/rasp/modes.h"

void learning(char* dirPath, Server server) {
  IplImage image;
  int angle;
  int landmarksNbr;

//  image = getPlace();
  landmarksNbr = learnLocation(dirPath);
  angle = receiveAngleFromClient(server);
  savePlaceData(dirPath, angle, landmarksNbr);
}

void autonomous() {
//  Place places[] = LoadPlaces();
  IplImage image;
  int cont = 1, placeIndex, angle;

  while(cont) {
    //image = getPlace();
    //imageTreatment(image);

    //placeIndex = recognition(image);
    //angle = places[placeIndex].depl;
  }

}
