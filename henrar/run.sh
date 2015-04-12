mpicc -o lab4.out lab4mpi.c -lrt -lm

mpiexec -n 1 ./lab4.out
mpiexec -n 2 ./lab4.out
mpiexec -n 4 ./lab4.out
mpiexec -n 6 ./lab4.out
mpiexec -n 8 ./lab4.out
mpiexec -n 10 ./lab4.out
mpiexec -n 12 ./lab4.out
