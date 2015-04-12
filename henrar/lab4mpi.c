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

    long numberOfIterations = 1000000;
    double x,y;                     //x,y value for the random coordinate
    int count = 0;                 //Count holds all the number of how many good coordinates
    double z;                       //Used to check if x^2+y^2<=1
    double pi;                      //holds approx value of pi
    int nodeNumber;
    int received[nodeNumber];
    long receivedNumberOfIterations[nodeNumber];
    srand(SEED);                        //Give rand() a seed value

    if(*world_rank != 0)
    {
        for (int i = 0; i < numberOfIterations; ++i)                  //main loop
        {
            x= ((double)rand())/RAND_MAX;           //gets a random x coordinate
            y =((double)rand())/RAND_MAX;           //gets a random y coordinate
            z = sqrt(x*x+y*y);                  //Checks to see if number in inside unit circle
            if (z <= 1)
            {
                count++;                //if it is, consider it a valid random point
            }
        }
        for(int i = 0; i < nodeNumber; ++i)
        {
            MPI_Send(&count, 1, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
            MPI_Send(&numberOfIterations, 1, MPI_LONG, 0, world_rank, MPI_COMM_WORLD);
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

    if (*world_rank == 0)                      //if root process
    {
        int finalcount = 0;
        long finalnumberOfIterations = 0;
        for(int i = 0; i < nodeNumber; ++i)
        {
            finalcount += received[i];
            finalnumberOfIterations += receivedNumberOfIterations[i];
        }

        pi = ((double)finalcount/(double)finalnumberOfIterations)*4.0;               //p = 4(m/n)
        printf("Pi: %f\n", pi);             //Print the calculated value of pi

    }
}

int main(int argc, char* argv[])
{
    int world_rank = 0;
    int world_size = 0;
    initMPI(&world_size, &world_rank);
    printf("World size: %i , World rank: %i \n", world_size, world_rank);
    MPI_Finalize();
    return 0;
}