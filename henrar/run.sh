mpicc -o lab4.out lab4mpi.c -std=gnu99 -lrt -lm

mpiexec -n 1 ./lab4.out 1000000 -b
mpiexec -n 2 ./lab4.out 1000000 -b
mpiexec -n 4 ./lab4.out 1000000 -b
mpiexec -n 6 ./lab4.out 1000000 -b
mpiexec -n 8 ./lab4.out 1000000 -b
mpiexec -n 10 ./lab4.out 1000000 -b
mpiexec -n 12 ./lab4.out 1000000 -b

mpiexec -n 1 ./lab4.out 10000000 -b
mpiexec -n 2 ./lab4.out 10000000 -b
mpiexec -n 4 ./lab4.out 10000000 -b
mpiexec -n 6 ./lab4.out 10000000 -b
mpiexec -n 8 ./lab4.out 10000000 -b
mpiexec -n 10 ./lab4.out 10000000 -b
mpiexec -n 12 ./lab4.out 10000000 -b

mpiexec -n 1 ./lab4.out 10000000 -b
mpiexec -n 2 ./lab4.out 10000000 -b
mpiexec -n 4 ./lab4.out 10000000 -b
mpiexec -n 6 ./lab4.out 10000000 -b
mpiexec -n 8 ./lab4.out 10000000 -b
mpiexec -n 10 ./lab4.out 10000000 -b
mpiexec -n 12 ./lab4.out 10000000 -b

mpiexec -n 1 ./lab4.out 1000000000 -b
mpiexec -n 2 ./lab4.out 1000000000 -b
mpiexec -n 4 ./lab4.out 1000000000 -b
mpiexec -n 6 ./lab4.out 1000000000 -b
mpiexec -n 8 ./lab4.out 1000000000 -b
mpiexec -n 10 ./lab4.out 1000000000 -b
mpiexec -n 12 ./lab4.out 1000000000 -b

mpiexec -n 1 ./lab4.out 1000000 -sc
mpiexec -n 2 ./lab4.out 1000000 -sc
mpiexec -n 4 ./lab4.out 1000000 -sc
mpiexec -n 6 ./lab4.out 1000000 -sc
mpiexec -n 8 ./lab4.out 1000000 -sc
mpiexec -n 10 ./lab4.out 1000000 -sc
mpiexec -n 12 ./lab4.out 1000000 -sc

mpiexec -n 1 ./lab4.out 10000000 -sc
mpiexec -n 2 ./lab4.out 10000000 -sc
mpiexec -n 4 ./lab4.out 10000000 -sc
mpiexec -n 6 ./lab4.out 10000000 -sc
mpiexec -n 8 ./lab4.out 10000000 -sc
mpiexec -n 10 ./lab4.out 10000000 -sc
mpiexec -n 12 ./lab4.out 10000000 -sc

mpiexec -n 1 ./lab4.out 10000000 -sc
mpiexec -n 2 ./lab4.out 10000000 -sc
mpiexec -n 4 ./lab4.out 10000000 -sc
mpiexec -n 6 ./lab4.out 10000000 -sc
mpiexec -n 8 ./lab4.out 10000000 -sc
mpiexec -n 10 ./lab4.out 10000000 -sc
mpiexec -n 12 ./lab4.out 10000000 -sc

mpiexec -n 1 ./lab4.out 1000000000 -sc
mpiexec -n 2 ./lab4.out 1000000000 -sc
mpiexec -n 4 ./lab4.out 1000000000 -sc
mpiexec -n 6 ./lab4.out 1000000000 -sc
mpiexec -n 8 ./lab4.out 1000000000 -sc
mpiexec -n 10 ./lab4.out 1000000000 -sc
mpiexec -n 12 ./lab4.out 1000000000 -sc