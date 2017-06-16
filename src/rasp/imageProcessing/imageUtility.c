#include "../../../include/rasp/imageProcessing/imageUtility.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../../include/rasp/imageProcessing/saveLoad.h"
#include "../../../include/serial/Serial.h"

/*For saving functions*/
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

#define __DEBUG

IplImage* concatenateImage(IplImage* image1, IplImage* image2, IplImage* image3) {

    int i, j, k;
    IplImage* result = cvCreateImage(cvSize(image1->width*3, image1->height), IPL_DEPTH_8U, 1);
    int width = image1->width;
    int height = image1->height;
    int nChannels = image1->nChannels;
    int step = image1->widthStep;
    int bigstep = result->widthStep;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            for(k = 0; k < nChannels; k++) {
                result->imageData[i*bigstep + j*nChannels + k] = image1->imageData[i*step + j*nChannels + k];
                result->imageData[i*bigstep + (j+width)*nChannels + k] = image2->imageData[i*step + j*nChannels + k];
                result->imageData[i*bigstep + (j+(width*2))*nChannels + k] = image3->imageData[i*step + j*nChannels + k];
            }
        }
    }

    return result;
}

IplImage* captureImage(){
    IplImage *image = 0;
    IplImage *gray = 0;
    CvCapture *capture;

    capture = cvCaptureFromCAM(CAMPORT); // 0 for local webcam, 1 for external webcam or -1 for any. Use 0 for ext webcam on rpi.
    image = cvQueryFrame(capture);
    if(!image)
    {
        puts("Image fail to load");
    }

    gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvCvtColor(image, gray, CV_RGB2GRAY);

    cvReleaseImage(&image);
    cvReleaseCapture(&capture);

    return gray;
}

ImageToLearn captureAll(int serialD, int placeNbr){

	char* bufferSerial = (char*)malloc(4 * sizeof(char));
	int i;
	int angle[] = ANGLES_CAPTURE;
	ImageToLearn images;
	char name[50];

	for(i = 0 ; i < NB_CAPTURE ; i++){
		turnServo(serialD, angle[i], bufferSerial);
		if(i == 0){
			usleep(1000 * 1000);
		}
		else{
			usleep(300 * 1000);
		}
		images.image[i] = captureImage();
		//usleep(500 * 1000);
		sprintf(name, "../saveImages/captureAll%.3d_%.3d.jpg", placeNbr, i);
		cvSaveImage(name, images.image[i], 0);
	}

	free(bufferSerial);

	return images;
}

void sobel(int64_t *curve, int64_t *derived, int nbrColumn)
{
    int i;
    if(derived == NULL)
    {
        fputs("NULL pointer exception in sobel",stderr);
        return ;
    }

    //Calcul du premier élément en créant une redondance de l'information
    derived[0] = -curve[0]+curve[1];

    for(i=1;i<nbrColumn-1;i++)
    {
        derived[i] = -curve[i-1]+curve[i+1];
    }

    //Calcul du dernier élément en créant une redondance de l'information
	derived[i] = -curve[i-1]+curve[i];
}

void lowFiltering(int64_t *curve, int64_t *smoothed, int nbrColumn, int size)
{
    int mean;
    int i, j;
    int iLeft, iRight;

    if(smoothed == NULL)
    {
        fputs("NULL pointer exception in lowFiltering",stderr);
        return ;
    }

    for(i = 0; i < nbrColumn; i++)
    {
        //On détermine les bornes à prendre en compte pour le filtre
        mean = 0;
        iLeft = i-size/2 >= 0 ? i-size/2 : 0;
        iRight = i+size/2 < nbrColumn ? i+size/2 : nbrColumn-1;

        for(j = iLeft; j <= iRight; j++)
        {
            mean += curve[j];
        }
        smoothed[i]=mean/(iRight-iLeft+1);
    }
}

Interest *extremumExtract(int64_t *curve, int64_t *derived, int *nbrElt, int nbrColumn, int threshold)
{
    int i, p;
    int *locations;
    Interest *extremums;


    p = 0;
    locations = (int *) malloc(nbrColumn*sizeof(int));

    for(i = 0; i < nbrColumn; i++)
    {
        locations[i] = -1;
    }


    for(i = LMSIZE; i < nbrColumn-LMSIZE+1; i++)
    {
        if(derived[i]*derived[i+1] < 0)
        {
            if(abs(derived[i+1]-derived[i]) > threshold)
            {
                locations[p] = i;

                p++;
            }
        }
    }

    extremums = malloc(p*sizeof(Interest));
    *nbrElt = p;

    while(--p >= 0)
    {
        extremums[p].index = locations[p];
        extremums[p].value = abs(derived[locations[p]+1]-derived[locations[p]]);
        //extremums[p].value = curve[p];
    }

    free(locations);

    return extremums;
}

static int compare (void const *a, void const *b)
{
    Interest const *pa = a;
    Interest const *pb = b;

    return pa->value - pb->value;
}

IplImage *compressedThumbnail(IplImage *image, int widthPos, int heightPos)
{
    int i, j;
	int k, l;
    IplImage *thumbnail = 0;
    int thumbnailPos, imagePos;

	#ifdef __DEBUG
	IplImage *color = 0;

	color = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
    cvCvtColor(image, color, CV_GRAY2RGB);
	#endif

    if(widthPos < LMSIZE || widthPos >= image->width-LMSIZE)
    {
        fputs("This position is not permitted in compressedThumbnail\n",stderr);
        return NULL;
    }

    thumbnail = cvCreateImage(cvSize(LMSIZE, LMSIZE), IPL_DEPTH_8U, 1);
    if(thumbnail == 0)
    {
        fputs("Allocation failed in compressedThumbnail\n",stderr);
        return NULL;
    }

    for(i = 0; i < LMSIZE; i++)
    {
        for(j = 0; j < LMSIZE; j++)
        {
            thumbnailPos = i * thumbnail->widthStep + j;
            imagePos = (SCALEY * i + heightPos - (0.5*SCALEY*LMSIZE)) * image->widthStep + (SCALEX * j + widthPos - (0.5*SCALEX*LMSIZE));
            thumbnail->imageData[thumbnailPos]=image->imageData[imagePos];

			#ifdef __DEBUG
			for(k = heightPos - (0.5*SCALEY*LMSIZE); k < heightPos + (0.5*SCALEY*LMSIZE); k++)
			{
				for(l = widthPos - (0.5*SCALEX*LMSIZE); l < widthPos + (0.5*SCALEX*LMSIZE); l++)
				{
					if(	k == heightPos - (0.5*SCALEY*LMSIZE) || l == widthPos - (0.5*SCALEX*LMSIZE) ||
						k == heightPos + (0.5*SCALEY*LMSIZE) - 1 ||	l == widthPos + (0.5*SCALEX*LMSIZE) - 1)
					{
						color->imageData[k*color->widthStep + l*color->nChannels] = 0;
						color->imageData[k*color->widthStep + l*color->nChannels+1] = 0;
						color->imageData[k*color->widthStep + l*color->nChannels+2] = 255;
					}
				}
			}
			#endif
        }
    }

	#ifdef __DEBUG
	cvSaveImage("../saveImages/contour.jpg", color, 0);
	cvReleaseImage(&color);
	#endif

    return thumbnail;
}

void getSumColumnValues(IplImage* image, int64_t* columnValues)
{
    int32_t i,j,k;
    if(columnValues == NULL)
    {
        fputs("The array in getSumColumnValues is NULL",stderr);
        return ;
    }

    for(i=0 ; i<image->width ; i++)
    {
        columnValues[i] = 0;
        for(j=0 ; j<image->height ; j++)
        {
            for(k=0 ; k<image->nChannels ; k++)
            {
                columnValues[i]	+= (uchar)image->imageData[j*image->widthStep+i*image->nChannels+k];
            }
        }
    }
}

void printGraphOnImage(IplImage* image, int64_t* columnValues)
{
    int i,k;
    int height = image->height;
    int width = image->width;
    int step = image->widthStep;
    int nChannels = image->nChannels;
    uchar *data = (uchar *)image->imageData;
    printf("step = %d, nCHannels = %d\n", step, nChannels);
    if(columnValues == NULL)
    {
        fputs(" in printGraphOnImage array not malloc\n", stderr);
        return;
    }
    for(i=0 ; i<width ; i++)
    {
        for(k=0 ; k<nChannels ; k++)
        {
            data[((((columnValues[i]/(255*nChannels))*-1)+height)*step) + i*nChannels + k] =
                255/*-data[(columnValues[i]/(255*nChannels))*step + i*nChannels + k]*/;
        }
    }
}

IplImage* getThumbnail(IplImage* image, int widthPos, int heightPos)
{
    IplImage* thumbnail = 0;

    cvSetImageROI(image, cvRect(widthPos, heightPos, 32, 32));
    thumbnail = cvCreateImage(cvSize(32, 32), image->depth, image->nChannels);
    cvCopy(image, thumbnail, NULL);
    cvResetImageROI(image);

    return thumbnail;
}

int compareImage(IplImage* current, IplImage* learned)
{
    const int range = 3;
    int width = current->width;
    int height = current->height;
    int step = current->widthStep;
    int nChannels = current->nChannels;
    float angle;
    int i,j,k;
    int recognition = 0;

    if(width != learned->width)
    {
        fputs("Widh aren't similar\n", stderr);
        return -1;
    }
    if(height != learned->height)
    {
        fputs("Height aren't similar\n", stderr);
        return -1;
    }
    if(step != learned->widthStep)
    {
        fputs("step aren't similar\n", stderr);
        return -1;
    }
    if(nChannels != learned->nChannels)
    {
        fputs("nChannels aren't similar\n", stderr);
        return -1;
    }
    for(i=0 ; i<height ; i++)
    {
        for(j=0 ; j<width ; j++)
        {
            for(k=0 ; k<nChannels ; k++)
            {
                /*Faut tester pour voir combien de delta on laisse pour la reconnaissance*/
                if(current->imageData[i*step+j*nChannels+k] > learned->imageData[i*step+j*nChannels+k]-range
                        && current->imageData[i*step+j*nChannels+k]<learned->imageData[i*step+j*nChannels+k]+range)
                {
                    recognition += 1;
                }
            }
        }
    }
    recognition = (100*recognition)/(height*width*nChannels);
    return recognition;
}

float diffComparison(IplImage* current, IplImage* learned){
    int width = current->width;
    int height = current->height;
    int step = current->widthStep;
    int nChannels = current->nChannels;
    int i,j,k;
    float diff = 0;

    if(width != learned->width)
    {
        fputs("Widh aren't similar\n", stderr);
        return -1;
    }
    if(height != learned->height)
    {
        fputs("Height aren't similar\n", stderr);
        return -1;
    }
    if(step != learned->widthStep)
    {
        fputs("step aren't similar\n", stderr);
        return -1;
    }
    if(nChannels != learned->nChannels)
    {
        fputs("nChannels aren't similar\n", stderr);
        return -1;
    }
    for(i=0 ; i<height ; i++)
    {
        for(j=0 ; j<width ; j++)
        {
            for(k=0 ; k<nChannels ; k++)
            {
                diff += abs(learned->imageData[i*step+j*nChannels+k] - current->imageData[i*step+j*nChannels+k]);
            }
        }
    }
    diff = diff/(float)(32*32*255);

    return diff;
}

void learnLocation(int serialD, Place *place, int placeNbr) {
    IplImage *thumbnail = 0;
    Interest *extremums;
    ImageToLearn images;
    int64_t *sumColumn;
    int64_t *smoothed;
    int64_t *derived;
    uint8_t *bufferW = (uint8_t *)malloc(4*sizeof(char));
    int nbrLandmarks, nbrElt, rAngle;
    float fAngle, angleI;
    const int angle[] = ANGLES_CAPTURE;
    char path[100];
    int i, l;

    nbrLandmarks = 0;
    rAngle = askAngle(serialD, bufferW);
    images = captureAll(serialD, placeNbr);

    sumColumn = malloc(images.image[0]->width * sizeof(int64_t));
    smoothed = malloc(images.image[0]->width * sizeof(int64_t));
    derived = malloc(images.image[0]->width * sizeof(int64_t));

    mkdir("../saveImages/thumbnails", 0777);
    for(l = 0; l < NB_CAPTURE; l++) {

      getSumColumnValues(images.image[l], sumColumn);
      lowFiltering(sumColumn, smoothed, images.image[l]->width, SMOOTHNESS);
      sobel(smoothed, derived, images.image[l]->width);
      extremums = extremumExtract(sumColumn, derived, &nbrElt, images.image[l]->width, SLOPE);
      qsort((void *) extremums, nbrElt, sizeof(Interest), compare);

      #ifdef __DEBUG
        IplImage *graph = 0;
        graph = cvCreateImage(cvSize(images.image[l]->width, images.image[l]->height), IPL_DEPTH_8U, 1);
        printGraphOnImage(graph, smoothed);
        cvSaveImage("../saveImages/smoothed.jpg", graph, 0);
        cvReleaseImage(&graph);
    	#endif

      for(i  = 0; i < NB_LANDMARKS_IND && i < nbrElt; i++) {
          sprintf(path, "../saveImages/thumbnails/thumbnails%.3d.jpg", nbrLandmarks);

          thumbnail = compressedThumbnail(images.image[l], extremums[i].index, HEIGHTPOS);
          fAngle = (((float)extremums[i].index / images.image[l]->width)*CAMERA_VISION_ANGLE) - (CAMERA_VISION_ANGLE/2);
  		    place->landmarks[nbrLandmarks].index = extremums[i].index;
  		    place->landmarks[nbrLandmarks].thumbnail = thumbnail;
          angleI = rAngle + (CAMERA_ROTATION*l - 90) + fAngle;
          if(angleI < 0 ) {
            place->landmarks[nbrLandmarks].angle = angleI + 360;
          }
          else if(angleI >= 360 ) {
            place->landmarks[nbrLandmarks].angle = angleI - 360;
          }
          else {
            place->landmarks[nbrLandmarks].angle = angleI;
          }
          place->landmarks[nbrLandmarks].angle = (place->landmarks[nbrLandmarks].angle*M_PI)/180;
  //        printf("L'angle initial est de %f, l'angle en radian est de %f, angle bousosle est %d\n", angleI, place->landmarks[nbrLandmarks].angle, rAngle);
  //        cvSaveImage(path, thumbnail, 0);
  //        cvReleaseImage(&thumbnail);

          nbrLandmarks++;
      }

    }
    place->landmarksNbr = nbrLandmarks;
    place->movementVectorAngle = rAngle;

    #ifdef __DEBUG
  	  IplImage *graphOnImage = 0;
  	  graphOnImage = cvLoadImage("../saveImages/contour.jpg", CV_LOAD_IMAGE_COLOR);
  	  printGraphOnImage(graphOnImage, smoothed);
      cvSaveImage("../saveImages/graphOnImage.jpg", graphOnImage, 0);
      cvReleaseImage(&graphOnImage);
  	#endif

    free(bufferW);
    free(sumColumn);
    free(smoothed);
    free(derived);
    free(extremums);

		for(l = 0; l < NB_CAPTURE; l++) {
			cvReleaseImage(&(images.image[l]));
		}
}
