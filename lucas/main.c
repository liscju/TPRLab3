#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "mtwist.h"

/* globals */
int numProcs, myId, mpi_err;
long double PI = 3.141592653589793238462643;
long long int pointCount;
/* end globals  */

/* helper function declarations */
void initMPI(int, char**);
long long int power(int base, int exp);
/* end helper function declarations */

int main(int argc, char** argv) {
	initMPI(argc, argv);

	long double pi = PI;
	pointCount = atoll(argv[1]);
	mt_seed();
	int i;
	for(i = 0; i < 10; ++i) {
		printf("%d: %ld\n", myId, mt_lrand()%100);
	}

	MPI_Finalize();
}

/* helper function decfinitions */
void initMPI(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
}

long long int power(int base, int exp) {
	long long int output = 1;	
	while(exp > 0) {
		output *= base;
		exp--;
	}

	return output;
}
/* end helper function decfinitions */
