__author__ = 'lee'

# Oblicza PI znajdujace sie w 
# kwadracie -1<=x<=1 -1<=y<=1
class PiCalculator:
    def __init__(self, experimentCount, radius, rand2DGen):
        assert experimentCount > 0 and radius > 0
        self.experimentCount = experimentCount
        self.radius = radius
        self.rand2DGen = rand2DGen

    def execute(self):
        circle_count = 0

        for i in range(0, self.experimentCount):
            x = self.rand2DGen.generate(-self.radius, self.radius)
            y = self.rand2DGen.generate(-self.radius, self.radius)

            if self.__is_point_inside_circle(x, y):
                circle_count += 1

        return circle_count

    def __is_point_inside_circle(self, x, y):
        return x * x + y * y < self.radius * self.radius

    @staticmethod
    def calculate_pi(circle_points_count, all_points_count):
        return (4 * circle_points_count) / float(all_points_count)
                
            

























