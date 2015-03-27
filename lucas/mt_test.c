#include <stdio.h>

#include "mtwist.h"

#define N 10
#define ITERATION_COUNT 1000000

int tab[N];

int main(int agrc, char** argv) {
	int i;
	
	mt_seed();

	for(i=0; i<ITERATION_COUNT; i++) {
		tab[mt_lrand()%N]++;
	}

	for(i=0; i<N; i++) {
		printf("%d: %d\n", i, tab[i]); 
	}
}
