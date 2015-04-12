#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <sys/time.h>
 
double calculateTimeDifference(struct timespec * endTime, struct timespec * beginTime)
{
    return ((double)endTime->tv_sec + 1.0e-9*endTime->tv_nsec) - ((double)beginTime->tv_sec + 1.0e-9*beginTime->tv_nsec);
}

int main(int argc, char* argv[])
{
    unsigned int numberOfIterations[6] = {10, 100, 10000, 100000, 1000000, 10000000};
    double x, y;
    int count = 0;
    double z;
    double pi;
    srand(time(NULL));
    struct timespec beginTime;
    struct timespec endTime;
    double timeDifference = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &beginTime);
    for(int j = 0; j < sizeof(numberOfIterations); j++)
    {
        for (int i = 0; i < numberOfIterations; ++i)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            z = sqrt((x*x)+(y*y));
            if(z <= 1)
            {
                count++;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        timeDifference = calculateTimeDifference(&endTime, &beginTime);
        pi = ((double)count/(double)numberOfIterations)*4.0;   
        std::cout << "PI calculated in: " << numberOfIterations[j] << " is: " << pi << std::endl;
        std::cout << "Executed in: " << timeDifference << std::endl;
    }
    return 0;
}