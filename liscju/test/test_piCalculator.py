from unittest import TestCase
from calculators import PiCalculator
from randoms import TypicalRand2DGenerator

__author__ = 'lee'


class TestPiCalculator(TestCase):
    def test_calculate(self):
        pi_calc = PiCalculator(10000,TypicalRand2DGenerator() )
        pi = pi_calc.calculate()
        print "%.10f" % pi