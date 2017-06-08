/* Possibilité de faire un fichier header */
#include "../../include/rasp/imageProcessing/imageUtility.h"
#include "../../include/rasp/imageProcessing/saveLoad.h"
#include "../../include/serial/Serial.h"
#include "../../include/rasp/modes.h"
#include "../../include/rasp/server/server.h"
#include <stdio.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

#define __DEBUG 0

int main(int* argv, char** argc) {
	int serialD = open_s();
	Place *place;
	char* dirpath = (char *)malloc(50*sizeof(char));
	Server server;
	int deplAngle;
	int i = 0;

//	initialiseServer(&server);

	/* Leaning mode */
/*  while(strcmp(receiveFromClient(Server server), "Lea") == 0) {
		sendEndMsgToClient(server, "Rcd");

	//	sprintf(dirpath, "saveImages/Place%.3d", i);
	//	mkdir(dirpath, 0777);

    angle = receiveAngleFromClient(server);
		sendEndMsgToClient(server, "Rcd");
		place = learning(dirpath, deplAngle, serialD);
		savePlaceData(place, i);
		saveImage(place, i);
		sendEndMsgToClient(server, "End");
		i++;
  }*/


	/* Autonomous Mode */
/*	if(strcmp(receiveFromClient(Server server), "Aut") == 0) {
		sendEndMsgToClient(server, "Rcd");
		autonomous(serialD, server);
		sendEndMsgToClient(server, "End");
	}*/
	IplImage* image = captureAll(serialD);
	place = learnLocation(image, serialD, 90);
	savePlaceData(place, 0);
	saveImage(place, 0);

	free(place);
	free(dirpath);
	close_s(serialD);
//	closeServer(&server);

	return 0;
}
