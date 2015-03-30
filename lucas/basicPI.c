#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "mtwist.h"

#define TRUE 1
#define FALSE 0

/* globals */
double PI = 3.141592653589793238462643;
long long int pointCount;
/* end globals  */

/* helper function declarations */
int isInCircle(double x, double y);
/* end helper function declarations */

int main(int argc, char** argv) {
	if(argc != 2) {
		fprintf(stderr, "Wrong arguments. Usage: %s <number-of-points>\n", argv[0]);
		return EXIT_FAILURE;
	}
	pointCount = atoll(argv[1]);
	long long int pointsInCircle = 0;
	mt_seed();

	long long int i;
	double x, y;
	for(i = 0; i < pointCount; i++) {
		x = mt_drand();
		y = mt_drand();
		if(isInCircle(x, y) == TRUE) {
			pointsInCircle++;
		}
	}
	double myPI = (double)pointsInCircle/(double)pointCount;
	printf("  PI: %.15f\n", PI);	
	printf("MyPI: %.15f\n", myPI*4);

	return EXIT_SUCCESS;
}

/* helper function decfinitions */
int isInCircle(double x, double y) {
	if(sqrt(x*x+y*y) <= 1) {
		return TRUE;
	} else {
		return FALSE;
	}
}
/* end helper function decfinitions */
