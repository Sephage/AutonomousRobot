#include "./imageProcessing/imageUtility.h"
#include "./server/server.h"
#include <cv.h>

#ifndef MODES_H
#define MODES_H

void learning(char* dirPath, int angle, int serialD);
void autonomous(int serialD, Server server);

#endif
