mpicc -o main.out mtwist.c main.c -lrt
mpiexec -n 3  ./main.out 10000000
mpiexec -n 5  ./main.out 100000000
mpiexec -n 10 ./main.out 1000000000
