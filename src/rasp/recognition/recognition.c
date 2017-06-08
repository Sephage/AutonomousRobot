#include "../../../include/rasp/imageProcessing/imageUtility.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../../include/rasp/recognition/recognition.h"

#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define __DEBUG

int winner(Place *places, Place *current, int placesNbr)
{
	int i;
	int index;
	float minimum;
	float activity;

	index = -1;
	minimum = FLT_MAX;
	for(i = 0; i < placesNbr; i++)
	{
		activity = computeActivities(&places[i], current);

		if(activity < minimum)
		{
			minimum = activity;
			index = i;
		}
	}

	#ifdef __DEBUG
	printf("La place courrante correspond à la place %d\n", index);
	#endif

	return index;
}

float computeActivities(Place *place, Place *current)
{
	int i, j;
	float minimum;
	float activity;
	float evaluation;

	
	activity = 0;

	for(i = 0; i < current->landmarksNbr; i++)
	{
		minimum = FLT_MAX;

		for(j = 0; j < place->landmarksNbr; j++)
		{
			evaluation = diffComparison((current->landmarks[i]).thumbnail, (place->landmarks[j]).thumbnail) *
			fabs( ((place->landmarks[j]).angle - (current->landmarks[i]).angle)/M_PI );

			if(evaluation < minimum)
			{
				#ifdef __DEBUG
				printf("L'imagette %d correspond à l'imagette %d\n", i, j);
				#endif
				minimum = evaluation;
			}
		}

		activity += minimum;
	}

	#ifdef __DEBUG
	printf("L'activité totale est de %lf\n", activity);
	#endif

	return activity;
}
