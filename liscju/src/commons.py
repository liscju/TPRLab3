__author__ = 'lee'
import time

def time_observer(func):
    def calc_time(self,*args,**kwargs):
        t_start = time.time()
        ret = func(self,*args,**kwargs)
        t_end = time.time()
        elapsed_time = t_end - t_start
        print "Elapsed time for (" + self.name + ")= " + str(elapsed_time)
        return ret
    return calc_time