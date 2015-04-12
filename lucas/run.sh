mpicc -o main.out main.c -lrt -lm
#basic					10^7
mpiexec -n 1  ./main.out 10000000 -b
mpiexec -n 2  ./main.out 10000000 -b
mpiexec -n 4  ./main.out 10000000 -b
mpiexec -n 6  ./main.out 10000000 -b
mpiexec -n 8  ./main.out 10000000 -b
mpiexec -n 10 ./main.out 10000000 -b
mpiexec -n 12 ./main.out 10000000 -b
#						10^8
mpiexec -n 1  ./main.out 100000000 -b
mpiexec -n 2  ./main.out 100000000 -b
mpiexec -n 4  ./main.out 100000000 -b
mpiexec -n 6  ./main.out 100000000 -b
mpiexec -n 8  ./main.out 100000000 -b
mpiexec -n 10 ./main.out 100000000 -b
mpiexec -n 12 ./main.out 100000000 -b
#						10^9
mpiexec -n 1  ./main.out 1000000000 -b
mpiexec -n 2  ./main.out 1000000000 -b
mpiexec -n 4  ./main.out 1000000000 -b
mpiexec -n 6  ./main.out 1000000000 -b
mpiexec -n 8  ./main.out 1000000000 -b
mpiexec -n 10 ./main.out 1000000000 -b
mpiexec -n 12 ./main.out 1000000000 -b

mpiexec -n 3 ./main.out 10000000 -b
mpiexec -n 3 ./main.out 100000000 -b
