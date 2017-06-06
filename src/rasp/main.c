/* Possibilité de faire un fichier header */
#include "../../include/rasp/imageProcessing/imageUtility.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#define __DEBUG 0

int main(int* argv, char** argc)
{
    Place place;
    Place placeToLoad;
    place.movementVectorAngle = 0.564;
    place.landmarksNbr = 2;

    place.landmarks[0].angle = 95.5;
    place.landmarks[0].thumbnail = captureImage();

    place.landmarks[1].angle = 56.23;
    place.landmarks[1].thumbnail = captureImage();

    savePlaceData(&place, 1);
    loadPlaceData(&placeToLoad, 1);
    return 0;
}
