import time
from random import Random

__author__ = 'lee'

# Informacja jak generowac seed
# http://stackoverflow.com/questions/8920411/possible-sources-for-random-number-seeds
def generate_seed(worker_id):
    seconds = time.time()
    seed = abs(((seconds * 181) * ((worker_id - 83) * 359)) % 104729)
    return seed

class Rand2DGenerator:
    def generate(self,y_min,y_max):
        pass

class TypicalRand2DGenerator(Rand2DGenerator):
    def __init__(self,worker_id = None):
        if worker_id is None:
            self.random_generator = Random()
        else:
            seed = generate_seed(worker_id)
            self.random_generator = Random(seed)

    def generate(self, y_min, y_max):
        return self.random_generator.uniform(y_min,y_max)