__author__ = 'lee'

# Rank dla procesu zakladany - 0
class PiThreadMaster:
    def __init__(self,experiment_count,radius):
        self.experiment_count = experiment_count
        self.radius = radius

    def execute(self):
        exps = PiThreadMaster.__gather_experiments_results()

    @staticmethod
    def __send_parameters_to_all(experiment_count, radius):
        pass

    @staticmethod
    def __gather_experiments_results():
        pass
