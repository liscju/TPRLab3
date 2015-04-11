from unittest import TestCase
from randoms import TypicalRand2DGenerator

__author__ = 'lee'


class TestTypicalRand2DGenerator(TestCase):
    def test_generate(self):
        gen = TypicalRand2DGenerator()
        assert gen.generate(-1,1) != gen.generate(-1,1) != gen.generate(-1,1)