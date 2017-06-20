/* Possibilité de faire un fichier header */
#include "../../include/rasp/imageProcessing/imageUtility.h"
#include "../../include/rasp/imageProcessing/saveLoad.h"
#include "../../include/serial/Serial.h"
#include "../../include/rasp/modes.h"
#include "../../include/rasp/server/server.h"
#include "../../include/rasp/recognition/recognition.h"

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

#include <cv.h>
#include <highgui.h>

#define __DEBUG 0

int main(int argc, char** argv) {
    int serialD = open_s();
    char *msg = (char *)malloc(BUF_SIZE_RCV*sizeof(char));
    Place *place = (Place *)malloc(sizeof(Place));;
    Place *placesLearned;
    Server server;
    char *cont =  (char *)malloc(sizeof(char));
    int i = 0, loop =1, j = 0;
    int c = 0;
    int nbrPlace = 0;
    int index;

    int mode = 2, sub = 0;
    extern char* optarg;
    extern int optind, opterr;

    uint8_t* buf = malloc(sizeof(uint8_t));

    while((c = getopt(argc, argv, "alt")) != -1){
        switch(c){
            case 'a':
                mode = 0;
                break;
            case 'l' :
                mode = 1;
                break;
            case 't':
                mode = 2;
                break;
            default:
                printf("Mode par défaut learning + autonome, -l: learning, -a: autonome");
                break;
        }
    }
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

        learnLocation(serialD, place, i);
        if((mode == 2 && sub == 0) || mode == 1){ //learning
            savePlaceData(place, i);
            saveImage(place, i);
            i++;
            nbrPlace++;
            printf("Continue learning? (Y/n)\n");
            while (c != '\n' && c != EOF)
            {
                c = getchar();
            }
            c = getchar();
            if(c == 'n' || c == 'N'){
                if(mode == 1){
                    saveNbPlace(nbrPlace);
                    loop = 0;
                }
                else
                    sub = 1;
            }
            for(j = 0; j < place->landmarksNbr; j++){
                if(place->landmarks[j].thumbnail != NULL) {
                    cvReleaseImage(&(place->landmarks[j].thumbnail));
                }
            }
        }
        else if(mode == 0 || (mode == 2 && sub == 1)){ //mode autonomie
            if(mode == 0){
                nbrPlace = loadNbPlace();
            }
            placesLearned = malloc(nbrPlace*sizeof(Place));

            loadPlacesData(placesLearned, nbrPlace);
            loadImages(placesLearned, nbrPlace);

            while(loop < 10){
                learnLocation(serialD, place, i);

                index = winner(placesLearned, place, NULL, nbrPlace);
                turn(serialD, placesLearned[index].movementVectorAngle, buf);
                driveMMS(serialD, 3000, buf);

                for(j = 0; j < place->landmarksNbr; j++){
                    if(place->landmarks[j].thumbnail != NULL) {
                        cvReleaseImage(&(place->landmarks[j].thumbnail));
                    }
                }
                loop++;
            }
            loop = 0;
        }
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
    free(place);
    close_s(serialD);
    //	closeServer(&server);

    return 0;
}
