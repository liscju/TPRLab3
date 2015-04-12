#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#define SEED 35791246
double piValue = 3.141592653589793238462643;

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

    char * tempNoIter = argv[1];
    long numberOfIterations = atoi(tempNoIter);
    double x,y;
    int count = 0;
    double z;
    double pi;
    int nodeNumber;
    int received[nodeNumber];
    long receivedNumberOfIterations[nodeNumber];
    srand(SEED);

    if(*world_rank != 0)
    {
        for (int i = 0; i < numberOfIterations; ++i)
        {
            x= ((double)rand())/RAND_MAX;
            y =((double)rand())/RAND_MAX;
            z = sqrt(x*x+y*y);
            if (z <= 1)
            {
                count++;
            }
        }
        for(int i = 0; i < nodeNumber; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC, &beginTime);
            MPI_Send(&count, 1, MPI_INT, 0, *world_rank, MPI_COMM_WORLD);
            MPI_Send(&numberOfIterations, 1, MPI_LONG, 0, *world_rank, MPI_COMM_WORLD);
        }
    }
    else if (*world_rank == 0)
    {
        for(int i = 0; i < nodeNumber; ++i)
        {
            MPI_Recv(&received[i], nodeNumber, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&receivedNumberOfIterations[i], nodeNumber, MPI_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (*world_rank == 0)
    {
        int finalcount = 0;
        long finalnumberOfIterations = 0;
        for(int i = 0; i < nodeNumber; ++i)
        {
            finalcount += received[i];
            finalnumberOfIterations += receivedNumberOfIterations[i];
        }
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        timeDifference = calculateTimeDifference(&endTime, &beginTime);
        pi = ((double)finalcount/(double)finalnumberOfIterations)*4.0;
        printf("Pi: %.15f\n", pi);

    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Must have 3 arguments\n");
        return 6;
    }
    int world_rank = 0;
    int world_size = 0;
    initMPI(&world_size, &world_rank);
    checkAndLaunchProcesses(&world_size, &world_rank, argv);
    printf("World size: %i , World rank: %i \n", world_size, world_rank);
    MPI_Finalize();
    return 0;
}