from commons import time_observer

__author__ = 'lee'

# Oblicza PI znajdujace sie w 
# kwadracie -1<=x<=1 -1<=y<=1
class PiCalculator:
    RANGE_MIN = -1
    RANGE_MAX =  1
    
    def __init__(self, experimentCount, rand2DGen):
        self.experimentCount = experimentCount
        self.rand2DGen = rand2DGen
        self.name = "PAROWKA"

    @time_observer
    def calculate(self):
        circle_count = 0
        
        for i in range(0,self.experimentCount):
            x = self.rand2DGen.generate(PiCalculator.RANGE_MIN,PiCalculator.RANGE_MAX)
            y = self.rand2DGen.generate(PiCalculator.RANGE_MIN,PiCalculator.RANGE_MAX)
            
            if self.__is_point_inside_circle(x,y):
                circle_count = circle_count + 1
                
        return self.__calculate_pi(circle_count,self.experimentCount)
        

    def __is_point_inside_circle(self, x, y):
        return x*x + y*y < 1

    def __calculate_pi(self, circle_points_count, all_points_count):
        return (4 * circle_points_count)/float(all_points_count)
                
            

























