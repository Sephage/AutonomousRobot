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
	char *msg = (char *)malloc(BUF_SIZE_RCV*sizeof(char));
	Place *place;
	Server server;
	char *cont =  (char *)malloc(sizeof(char));
	int i = 0, loop =1, j = 0;

//	initialiseServer(&server);

	/* Leaning mode */
/*  while(loop) {
		strcmp(receiveFromClient(server, msg), "Lea")
		sendEndMsgToClient(server, "Rcd");

		place = learnLocation(serialD, 15);
		savePlaceData(place, i);
		saveImage(place, i);
		sendEndMsgToClient(server, "End");
		i++;
  }*/

	while(loop) {
		place = (Place *)malloc(sizeof(Place));
		learnLocation(serialD, place);
		savePlaceData(place, i);
		saveImage(place, i);
		i++;
		printf("Continue learning? (Y/n)\n");
		scanf("%c", cont);
		if(strcmp((const char *)cont, "n") == 0 || strcmp((const char *)cont, "N") == 0) {
			loop = 0;
		}
		for(j = 0; j < place->landmarksNbr; j++){
			free(place->landmarks[j].thumbnail);
		}
		free(place);
	}


	/* Autonomous Mode */
/*	if(strcmp(receiveFromClient(Server server), "Aut") == 0) {
		sendEndMsgToClient(server, "Rcd");
		autonomous(serialD, server);
		sendEndMsgToClient(server, "End");
	}*/
/*	savePlaceData(place, 0);
	saveImage(place, 0);*/

	free(cont);
	free(msg);
	close_s(serialD);
//	closeServer(&server);

	return 0;
}
