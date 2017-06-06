/* Possibilité de faire un fichier header */
#include "../../include/rasp/imageProcessing/imageUtility.h"
#include "../../include/serial/Serial.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#define __DEBUG 0

int main(int* argv, char** argc)
{
	int serialD = open_s();
	learnLocation();
	close_s(serialD);
}
