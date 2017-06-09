#include "../../../include/rasp/imageProcessing/saveLoad.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"

#include <stdio.h>

/*For saving functions*/
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <cv.h>
#include <highgui.h>

const char* C_SAVE_DIR = "../saveImages";

int saveImages(Place* places, int nbPlace){
    int i;
    for(i=0; i<nbPlace; i++){
        saveImage(&places[i], i);
    }
    return 0;
}

int saveImage(Place* place, int placeNumber)
{
    char name[256];
    FILE* file;

    int j;
    const char* mVA = "movementVectorAngle ";
    const char* angle = "angle ";
    char oldDir[1024];

    if(getcwd(oldDir, sizeof(oldDir)) == NULL) printf("getcwd has problem in saveImage");

    chdir(C_SAVE_DIR);
    for(j=0 ; j<place->landmarksNbr ; j++){
        sprintf(name, "%d_%d.jpg", placeNumber,j);
        printf("Creation du fichier %s\n", name);
        cvSaveImage(name, place->landmarks[j].thumbnail, NULL);
    }

    chdir(oldDir);
    return 0;
}

void savePlacesData(Place* places, int numberPlaces){
    int i;

    for(i=0 ; i<numberPlaces ; i++){
        savePlaceData(&(places[i]), i);
    }
}

int savePlaceData(Place* place, int placeNumber){
    char name[256];
    FILE* file;

    int j;

    char oldDir[1024];

    if(getcwd(oldDir, sizeof(oldDir)) == NULL) printf("getcwd has problem in savePlaceData");
    chdir(C_SAVE_DIR);

    sprintf(name, "%d.sav", placeNumber);
    printf("Creation du fichier\n");
    file = fopen(name, "w+");

    fwrite(&(place->landmarksNbr), 5, 1, file);
    fwrite(" ", 1, 1, file);
    fwrite(&(place->movementVectorAngle), 6, 1, file);
    fwrite(" ", 1, 1, file);
    for(j=0 ; j<place->landmarksNbr ; j++){
        fwrite(&(place->landmarks[j].angle), 6, 1, file);
    }
    fclose(file);

    chdir(oldDir);
    return 0;
}

void saveNbPlace(int nbPlace){
    char oldDir[1024];
    char name[256];
    FILE* file;

    if(getcwd(oldDir, sizeof(oldDir)) == NULL) printf("getcwd has problem in saveNbPlace");
    chdir(C_SAVE_DIR);

    file = fopen("PlaceNb.sav", "w+");
    fwrite(&nbPlace, 5,1, file);
    fclose(file);
    chdir(oldDir);
}

void loadPlacesData(Place* places, int numberPlaces){
    char name[256];
    FILE* file;
    int i;

    for(i=0 ; i<numberPlaces ; i++){
        loadPlaceData(&(places[i]), i);
    }
}

void loadPlaceData(Place* place, int placeNumber){
    char name[256];
    FILE* file;
    int i;
    char empty[1];
    char oldDir[1024];

    if(getcwd(oldDir, sizeof(oldDir)) == NULL) printf("getcwd has problem in loadPlaceData");
    chdir(C_SAVE_DIR);

    sprintf(name, "%d.sav", placeNumber);
    printf("Lecture du fichier %s\n", name);
    file = fopen(name, "r+");

    fread(&(place->landmarksNbr), 5, 1, file);
    fread(empty, 1, 1, file);
    fread(&(place->movementVectorAngle), 6, 1, file);
    fread(empty, 1, 1, file);
    for(i=0 ; i<place->landmarksNbr ; i++){
        fread(&(place->landmarks[i].angle), 6, 1, file);
    }
    printf("lN : %d\n", place->landmarksNbr);
    printf("mvA : %f\n", place->movementVectorAngle);
    for(i=0 ; i<place->landmarksNbr ; i++){
        printf("LM %d = %f\n",i, place->landmarks[i].angle);
    }

    chdir(oldDir);
}

void loadImages(Place* places, int numberPlaces){
    char name[256];
    char oldDir[1024];

    int i, j;

    if(getcwd(oldDir, sizeof(oldDir)) == NULL) printf("getcwd has problem in loadPlaceData");
    chdir(C_SAVE_DIR);
    for(i=0 ; i<numberPlaces ; i++){
        for(j=0 ; j<places->landmarksNbr ; j++){
            sprintf(name, "%d_%d.jpg", i, j);
            places[i].landmarks[j].thumbnail = cvLoadImage(name, CV_LOAD_IMAGE_GRAYSCALE);
        }
    }
    chdir(oldDir);
}

int loadNbPlace(){
   int nbPlaces;
   FILE* file;

   file = fopen("../saveImages/PlaceNb.sav","r");
   if(fread(&nbPlaces, 5, 1, file) == 0) puts("ERROR reading nbplaces\n");
   fclose(file);

   return nbPlaces;
}
