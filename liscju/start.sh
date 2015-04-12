# src/main.py {sequence|concurrent  {basic|scale}} experiment_count radius
python src/main.py sequence basic 100 10
mpiexec -n 20 python src/main.py concurrent basic 100 10
mpiexec -n 20 python src/main.py concurrent scale 100 10
