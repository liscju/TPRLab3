from unittest import TestCase
from commons import get_experiment_part_for_current_worker

__author__ = 'lee'


class TestGet_experiment_count_for_current_worker(TestCase):

    def test_get_experiment_count_for_current_worker_one_worker(self):
        exp1 = get_experiment_part_for_current_worker(1,1,15)

        assert exp1 == 15

    def test_get_experiment_count_for_current_worker_two_workers_simple_division(self):
        exp1 = get_experiment_part_for_current_worker(1,2,8)
        exp2 = get_experiment_part_for_current_worker(2,2,8)

        assert exp1 == 4
        print exp2
        assert exp2 == 4

    def test_get_experiment_count_for_current_worker_two_workers_division_with_rest(self):
        exp1 = get_experiment_part_for_current_worker(1,2,11)
        exp2 = get_experiment_part_for_current_worker(2,2,11)

        assert exp1 == 5
        assert exp2 == 6

    def test_get_experiment_count_for_current_worker_hard_test(self):
        exp1 = get_experiment_part_for_current_worker(1,10,19)
        exp10 = get_experiment_part_for_current_worker(10,10,19)
        assert exp1 == 1
        assert exp10 == 10
