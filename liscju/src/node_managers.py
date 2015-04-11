import numpy as np
from mpi4py import MPI
from calculators import PiCalculator
from randoms import TypicalRand2DGenerator

MPI_ROOT = 0
__author__ = 'lee'

def synchronizeAll(comm):
    comm.barrier()

class PiSequenceWorker:
    def __init__(self,experiment_count,radius):
        self.experiment_count = experiment_count
        self.radius = radius

    def execute(self):
        pi_calc = PiCalculator(self.experiment_count,self.radius,TypicalRand2DGenerator())
        circle_points = pi_calc.execute()
        all_points = self.experiment_count
        calculated_pi = PiCalculator.calculate_pi(circle_points,all_points)
        print "SEQUENCE Calculated pi = " + str(calculated_pi)


class PiThreadMasterWorker:
    def __init__(self, comm, experiment_count):
        assert comm.rank == 0
        self.comm = comm
        self.experiment_count = experiment_count

    def execute(self):
        synchronizeAll(self.comm)
        circle_points = self.__gather_experiments_results()
        all_points = self.experiment_count

        calculated_pi = PiCalculator.calculate_pi(circle_points,all_points)
        print "CONCURRENT Calculated pi = " + str(calculated_pi)

    def __gather_experiments_results(self):
        result = self.comm.reduce(0, root=MPI_ROOT, op=MPI.SUM)
        return result


class PiThreadSlaveWorker:
    def __init__(self, comm, experiment_count, radius):
        assert comm.rank != 0
        self.comm = comm
        self.experiment_count = experiment_count
        self.radius = radius

    def execute(self):
        synchronizeAll(self.comm)
        result = self.__perform_experiment(self.experiment_count, self.radius)
        self.__inform_about_result(result)

    def __perform_experiment(self,experiment_count, radius):
        picalc = PiCalculator(experiment_count,radius,TypicalRand2DGenerator())
        return picalc.execute()

    def __inform_about_result(self, result):
        self.comm.reduce(result,root=MPI_ROOT, op=MPI.SUM)









