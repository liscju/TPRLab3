#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

#define SEED 35791246
#define TYPE_BASIC 0
#define TYPE_SCALING 1
#define TRUE 1
#define FALSE 0

double piValue = 3.141592653589793238462643;
double myPI, myPIfragment;
int type = 0;
FILE* timeFile;

void openFiles(long long int numberOfIterations)
{
    char filenameBuffer[100];
    char* typeString;
    if(type == TYPE_SCALING)
    {
        typeString = "scaling";
    } else
    {
        typeString = "normal";
    }
    sprintf(filenameBuffer, "%s.txt", typeString);
    timeFile = fopen(filenameBuffer, "a+");
}

void closeFiles()
{
    fclose(timeFile);
}

double absolute(double x)
{
    if(x < 0)
    {
        return x*-1;
    } else
    {
        return x;
    }
}

double myRandom()
{
    return (double)rand() / (double)RAND_MAX ;
}

int isInCircle(double x, double y)
{
    if(sqrt(x*x+y*y) <= 1)
    {
        return TRUE;
    } else
    {
        return FALSE;
    }
}

double calculateTimeDifference(struct timespec * endTime, struct timespec * beginTime)
{
    return ((double)endTime->tv_sec + 1.0e-9*endTime->tv_nsec) - ((double)beginTime->tv_sec + 1.0e-9*beginTime->tv_nsec);
}

void initMPI(int * world_size, int * world_rank)
{
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, world_size);
}

void checkAndLaunchProcesses(int * world_size, int * world_rank, char * argv[])
{
    struct timespec beginTime;
    struct timespec endTime;
    double timeDifference = 0.0;

    char * temp = argv[1];
    long long int numberOfIterations = atoll(temp);

    if(strcmp(argv[2], "-sc") == 0)
    {
        type = TYPE_SCALING;
    } else
    {
        type = TYPE_BASIC;
    }
    clock_gettime(CLOCK_MONOTONIC, &beginTime);

    if(*world_rank == 0)
    {
        openFiles(numberOfIterations);
    }

    if(type == TYPE_SCALING)
    {
        numberOfIterations *= (*world_size);
    }

    srand(time(NULL)+(*world_rank)*1000);

    long long int pointsInCircle = 0;
    long long int i;
    double x, y;
    int myCount = 0;
    for(i = *world_rank; i < numberOfIterations; i=i+(*world_size))
    {
        x = myRandom();
        y = myRandom();
        if(isInCircle(x, y) == TRUE)
        {
            pointsInCircle++;
        }
        myCount++;
    }
    myPIfragment = (double)pointsInCircle / (double)(numberOfIterations);
    MPI_Reduce(&myPIfragment, &myPI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(*world_rank == 0)
    {
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        timeDifference = calculateTimeDifference(&endTime, &beginTime);
        if(type == TYPE_SCALING)
        {
            timeDifference /= (*world_size);
        }
        myPI = myPI*4;
        int iterationsToSave = numberOfIterations/(*world_size);
        fprintf(timeFile, "%d\t%lld\t%f\n", *world_size, iterationsToSave, timeDifference);
        closeFiles();
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        return 6;
    }
    int world_rank = 0;
    int world_size = 0;
    initMPI(&world_size, &world_rank);
    checkAndLaunchProcesses(&world_size, &world_rank, argv);
    MPI_Finalize();
    return 0;
}