import time
__author__ = 'lee'


def pi_execute_observer(func):
    def execute_measure_time(args, kwargs, self):
        t_start = time.time()
        ret = func(self, *args, **kwargs)
        t_end = time.time()
        elapsed_time = t_end - t_start
        return elapsed_time, ret

    def calc_time(self, *args, **kwargs):
        elapsed_time, ret = execute_measure_time(args, kwargs, self)
        print "Elapsed time = " + str(elapsed_time)
        from calculators import PiCalculator
        print "Calculated PI = %.10f" % PiCalculator.calculate_pi(ret,self.experimentCount)
        return ret

    return calc_time