#include "../../../include/rasp/imageProcessing/imageUtility.h"
#include "../../../include/rasp/imageProcessing/imageStructs.h"
#include "../../../include/rasp/recognition/recognition.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int winner(Place *places, Place *current, int placesNbr)
{
	int i;
	int index;
	float minimum;
	float activity;

	index = -1;
	minimum = FLOAT_MAX;
	for(i = 0; i < placesNbr; i++)
	{
		activity = computeActivities(&places[i], current);

		if(activity < minimum)
		{
			minimum = activity;
			index = i;
		}
	}

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
		minimum = FLOAT_MAX;

		for(j = 0; j < place->landmarksNbr; j++)
		{
			evaluation = diffComparison((current->landmarks[i]).thumbnail, (place->landmarks[j]).thumbnail) *
			fabs( ((place->landmarks[j]).angle - (current->landmarks[i]).angle)/M_PI );

			if(evaluation < minimum)
			{
				minimum = evaluation;
			}
		}

		activity += minimum;
	}

	return activity;
}
