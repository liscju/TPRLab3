from unittest import TestCase
from calculators import PiCalculator
from randoms import TypicalRand2DGenerator

__author__ = 'lee'


class TestPiCalculator(TestCase):
    def test_calculate(self):
        experimentCount = 10000
        pi_calc = PiCalculator(experimentCount,200,TypicalRand2DGenerator())
        res = pi_calc.execute()
        pi = PiCalculator.calculate_pi(res,experimentCount)
        print "Result = " + str(pi)