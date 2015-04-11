from node_managers import PiThreadMaster, PiThreadSlave
from mpi4py import MPI

__author__ = 'lee'
MPI_ROOT = 0

def start_workers(comm):
    exp_count = 100
    radius = 10
    if comm.rank == MPI_ROOT:
        worker = PiThreadMaster(comm, exp_count, radius)
    else:
        worker = PiThreadSlave(comm, exp_count, radius)
    worker.execute()


def initialize_communication():
    return MPI.COMM_WORLD

def main():
    comm = initialize_communication()
    start_workers(comm)

if __name__ == '__main__':
    main()