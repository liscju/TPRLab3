mpicc -o main.out main.c mtwist.c -lrt -lm
mpiexec -n 3  ./main.out 1000000
mpiexec -n 5  ./main.out 10000000
mpiexec -n 10 ./main.out 100000000
