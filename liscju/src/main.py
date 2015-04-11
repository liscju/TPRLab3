from node_managers import PiThreadMaster, PiThreadSlave
from mpi4py import MPI
from sys import argv

__author__ = 'lee'
MPI_ROOT = 0

def start_workers(comm,exp_count,radius):
    if comm.rank == MPI_ROOT:
        worker = PiThreadMaster(comm, exp_count, radius)
    else:
        worker = PiThreadSlave(comm, exp_count, radius)
    worker.execute()

def initialize_communication():
    return MPI.COMM_WORLD

# Return experiment_count,radius(of single pi calculation)
def read_command_line_arguments():
    return int(argv[1]),int(argv[2])

def main():
    comm = initialize_communication()
    exp_count,radius = read_command_line_arguments()
    start_workers(comm,exp_count,radius)

if __name__ == '__main__':
    main()