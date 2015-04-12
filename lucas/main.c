#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <math.h>

#define MPI_ROOT_ID 0

#define TRUE 1
#define FALSE 0
#define TYPE_BASIC 0
#define TYPE_SCALING 1

/* globals */
int numProcs, myId, mpi_err;
double PI = 3.141592653589793238462643;
double myPI, myPIfragment;
long long int pointCount;
int type;
/* end globals  */

/* helper function declarations */
void initMPI(int, char**);
double myRandom();
int isInCircle(double x, double y);
double absolute(double x);
/* end helper function declarations */

int main(int argc, char** argv) {
	if(argc != 3) {
		fprintf(stderr, "Wrong arguments. Usage: %s <number-of-points> <-b(asic)/-s(caling)>\n", argv[0]);
		return EXIT_FAILURE;
	}
	pointCount = atoll(argv[1]);
	if(strcmp(argv[2], "-s") == 0) {
		type = TYPE_SCALING;
	} else {
		type = TYPE_BASIC;
	}
	srand(time(NULL)+myId*1000);

	initMPI(argc, argv);
	
	long long int pointsInCircle = 0;
	long long int i;
	double x, y;
	int myCount = 0;

	if(type == TYPE_SCALING) {
		pointCount *= numProcs;
	}

	for(i = myId; i < pointCount; i=i+numProcs) {
		x = myRandom();
		y = myRandom();
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

double myRandom() {
	return (double)rand() / (double)RAND_MAX ;
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
