/*
 * Take an image and save the image in the right place,
 * Put the right information into the saving configuration file.
 *
 * placeNumber : the number of the place that the image belong
 * place : The place we want to save (only thumbnails)
 */
int saveImage(Place* place, int placeNumber);

int saveImages(Place *places, int nbPlace);

void saveNbPlace(int nbPlace);


void savePlacesData(Place* places, int numberPlaces);

int savePlaceData(Place* place, int placeNumber);

void loadPlaceData(Place *place, int nbPlace);

void loadImages(Place *places, int numberPlaces);

