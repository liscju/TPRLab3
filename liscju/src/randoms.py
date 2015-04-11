__author__ = 'lee'
from random import uniform

class Rand2DGenerator:
    def generate(self,y_min,y_max):
        pass

class TypicalRand2DGenerator(Rand2DGenerator):
    def generate(self, y_min, y_max):
        return uniform(y_min,y_max)