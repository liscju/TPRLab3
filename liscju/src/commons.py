import time

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
            calculated_pi,elapsed_time =  measure_execution_time(func,self)
            print param + ": Elapsed time = " + str(elapsed_time)
            print param + ": Calculated PI = %.10f" % calculated_pi
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








