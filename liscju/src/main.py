from sys import argv

from mpi4py import MPI

from commons import calculate_all_experiments_count, calculate_experiment_count_per_worker, ExperimentInfo

from node_managers import PiThreadMasterWorker, PiThreadSlaveWorker, PiSequenceWorker


__author__ = 'lee'
MPI_ROOT = 0


class Main:
    def __init__(self, calculate_starter_fun):
        self.func = calculate_starter_fun

    def main(self):
        speedup_type, exp_count, radius = Main.read_command_line_arguments()
        self.func(speedup_type, exp_count, radius)

    @staticmethod
    # Return speedup_type,experiment_count,radius(of single pi calculation)
    def read_command_line_arguments():
        return argv[1], int(argv[2]), int(argv[3])


def start_sequence_worker(speedup_type, experiment_count, radius):
    assert speedup_type == "basic"
    experiment_info = ExperimentInfo(False,speedup_type,1,experiment_count)
    worker = PiSequenceWorker(experiment_count, radius, experiment_info)
    worker.execute()


def start_concurrent_workers(speedup_type, experiment_count, radius):
    comm = MPI.COMM_WORLD
    worker_count = comm.size - 1
    experiment_info = ExperimentInfo(True,speedup_type,worker_count,experiment_count)
    assert worker_count > 0
    if comm.rank == MPI_ROOT:
        all_experiment_count = calculate_all_experiments_count(experiment_count, speedup_type, worker_count)
        worker = PiThreadMasterWorker(comm, all_experiment_count, experiment_info)
    else:
        worker_experiment_count = calculate_experiment_count_per_worker(comm, experiment_count, speedup_type,
                                                                        worker_count)

        worker = PiThreadSlaveWorker(comm, worker_experiment_count, radius, experiment_info)
    worker.execute()
    MPI.Finalize()


def usage():
    print "Usage: "
    print argv[0] + " {sequence|concurrent} {basic|scale} experiment_count radius_of_pi_calculation"
    exit(0)


if __name__ == '__main__':
    prog_type = argv.pop(1)
    if prog_type == "concurrent":
        Main(start_concurrent_workers).main()
    elif prog_type == "sequence":
        Main(start_sequence_worker).main()
    else:
        usage()