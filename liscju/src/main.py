from calculators import PiCalculator
from commons import get_experiment_count_for_current_worker
from node_managers import PiThreadMasterWorker, PiThreadSlaveWorker, PiSequenceWorker
from mpi4py import MPI
from sys import argv
from randoms import TypicalRand2DGenerator

__author__ = 'lee'
MPI_ROOT = 0

class Main:
    def __init__(self,calculate_starter_fun):
        self.func = calculate_starter_fun

    def main(self):
        exp_count, radius = Main.read_command_line_arguments()
        self.func(exp_count, radius)

    @staticmethod
    # Return experiment_count,radius(of single pi calculation)
    def read_command_line_arguments():
        return int(argv[1]), int(argv[2])

def start_sequence_worker(experiment_count,radius):
    worker = PiSequenceWorker(experiment_count,radius)
    worker.execute()

def start_concurrent_workers(experiment_count, radius):
    comm = MPI.COMM_WORLD
    worker_count = comm.size - 1
    assert worker_count > 0
    if comm.rank == MPI_ROOT:
        worker = PiThreadMasterWorker(comm, experiment_count)
    else:
        worker_experiment_count = get_experiment_count_for_current_worker(comm.rank, worker_count, experiment_count)
        worker = PiThreadSlaveWorker(comm, worker_experiment_count, radius)
    worker.execute()


if __name__ == '__main__':
    prog_type = argv.pop(1)
    if prog_type == "concurrent":
        Main(start_concurrent_workers).main()
    elif prog_type == "sequence":
        Main(start_sequence_worker).main()
