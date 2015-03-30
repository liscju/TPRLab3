#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "mtwist.h"

#define MPI_ROOT_ID 0

#define TRUE 1
#define FALSE 0

/* globals */
int numProcs, myId, mpi_err;
double PI = 3.141592653589793238462643;
double myPI, myPIfragment;
long long int pointCount;
/* end globals  */

/* helper function declarations */
void initMPI(int, char**);
int isInCircle(double x, double y);
double absolute(double x);
/* end helper function declarations */

int main(int argc, char** argv) {
	if(argc != 2) {
		fprintf(stderr, "Wrong arguments. Usage: %s <number-of-points>\n", argv[0]);
		return EXIT_FAILURE;
	}

	initMPI(argc, argv);

	pointCount = atoll(argv[1]);
	mt_seed();
	
	long long int pointsInCircle = 0;
	long long int i;
	double x, y;
	int myCount = 0;
	for(i = myId; i < pointCount; i=i+numProcs) {
		x = mt_drand();
		y = mt_drand();
		if(isInCircle(x, y) == TRUE) {
			pointsInCircle++;
		}
		myCount++;
	}
	myPIfragment = (double)pointsInCircle / (double)(pointCount);
	MPI_Reduce(&myPIfragment, &myPI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(myId == MPI_ROOT_ID) {
		myPI = myPI*4;
		printf("  PI: %.15f\n", PI);	
		printf("MyPI: %.15f\n", myPI);
		printf("diff: %.15f\n\n", absolute(PI-myPI));
	}

	MPI_Finalize();
}

/* helper function decfinitions */
void initMPI(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
}

int isInCircle(double x, double y) {
	if(sqrt(x*x+y*y) <= 1) {
		return TRUE;
	} else {
		return FALSE;
	}
}

double absolute(double x) {
	if(x<0) {
		return x*-1;
	} else {
		return x;
	}
}
/* end helper function decfinitions */
