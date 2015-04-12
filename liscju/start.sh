# src/main.py {sequence|concurrent  {basic|scale}} experiment_count radius
#python src/main.py sequence basic 100 10
#mpiexec -n 20 python src/main.py concurrent basic 100 10
#mpiexec -n 20 python src/main.py concurrent scale 100 10

function initialize_result_file {
    rm -f result.txt
    touch result.txt
}

R=10
N="10000000 1000000000 100000000000"
P="3 4 5 6 7 8 9 10"

initialize_result_file
for PROBLEM_SIZE in $N;do
    python src/main.py sequence basic $PROBLEM_SIZE $R >> result.txt
    for PROCESSORS in $P;do
        echo "Problem Size: $PROBLEM_SIZE Nodes : $PROCESSORS in progress...."
        mpiexec -n $PROCESSORS python src/main.py concurrent basic $PROBLEM_SIZE $R >> result.txt
        mpiexec -n $PROCESSORS python src/main.py concurrent scale $PROBLEM_SIZE $R >> result.txt
    done
done

