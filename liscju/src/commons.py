import time
import math

__author__ = 'lee'

def measure_execution_time(func,self):
    t_start = time.time()
    ret = func(self)
    t_end = time.time()
    elapsed_time = t_end - t_start
    return ret , elapsed_time

def pi_execute_reporter(param):
    def _(func):
        def __(self):
            calculated_pi,elapsed_time = measure_execution_time(func, self)
            result_presenter = CalculationResultPresenter(param, self.experiment_info, calculated_pi, elapsed_time)
            result_presenter.show()
            return calculated_pi
        return __
    return _


def get_experiment_part_for_current_worker(curr_worker, workers_count, experiment_count):
    assert curr_worker > 0 and workers_count > 0 and \
           experiment_count > 0 and curr_worker <= workers_count <= experiment_count

    if curr_worker < workers_count or workers_count == 1:
        return experiment_count // workers_count
    else:
        return experiment_count - ((workers_count - 1) * (experiment_count // workers_count))


def calculate_all_experiments_count(experiment_count, speedup_type, worker_count):
    if speedup_type == "basic":
        all_experiment_count = experiment_count
    else:
        assert speedup_type == "scale"
        all_experiment_count = experiment_count * worker_count
    return all_experiment_count


def calculate_experiment_count_per_worker(comm, experiment_count, speedup_type, worker_count):
    if speedup_type == "basic":
        worker_experiment_count = get_experiment_part_for_current_worker(comm.rank, worker_count, experiment_count)
    else:
        assert speedup_type == "scale"
        worker_experiment_count = experiment_count
    return worker_experiment_count


class ExperimentInfo:
    def __init__(self, is_concurrent, speedup_type,worker_count,experiment_count):
        self.is_concurrent = is_concurrent
        self.speedup_type = speedup_type
        self.worker_count = worker_count
        self.experiment_count = experiment_count

class CalculationResultPresenter:
    def __init__(self, param, experiment_info, calculated_pi, elapsed_time):
        self.param = param
        self.experiment_info = experiment_info
        self.calculated_pi = calculated_pi
        self.elapsed_time = elapsed_time

    def show(self):
        print "==============ExperimentInfo=============="
        N = self.experiment_info.experiment_count
        P = self.experiment_info.worker_count
        print "N = " + str(N)
        print "P = " + str(P)

        if self.experiment_info.is_concurrent:
            print "CONCURRENT"

            print self.experiment_info.speedup_type.upper()
            if self.experiment_info.speedup_type == "basic":
                print "T(P) = T(P,1) = " + str(self.elapsed_time)
            else:
                assert self.experiment_info.speedup_type == "scale"
                print "T(P,P) = " + str(self.elapsed_time)
        else:
            print "SEQUENCE"
            print "T(1)= T(1,1) = " + str(self.elapsed_time)

        print "Calculated PI = %.10f" % self.calculated_pi
        difference = abs(self.calculated_pi - math.pi)
        print "Difference between calc PI and real = %.10f" % difference

        print "=========================================="









