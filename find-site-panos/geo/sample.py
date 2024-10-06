from geopy import distance

import math
from typing import Generator

class Sample:
    def __init__(self, p1: tuple[float, float], p2: tuple[float, float], resolution: float):
        self.p1 = p1
        self.p2 = p2
        self.resolution = resolution

    def generate_latlon_samples(self) -> Generator[tuple[float, float], None, None]:
        dx, dy = self.xy_dist()
        x_dist = (self.p2[1] - self.p1[1]) / math.ceil(dx / abs(self.resolution))
        y_dist = (self.p2[0] - self.p1[0]) / math.ceil(dy / abs(self.resolution))
        return ((lat, lon) for lon in Sample.generate_samples(self.p1[1], self.p2[1], x_dist)
                for lat in Sample.generate_samples(self.p1[0], self.p2[0], y_dist))
    
    # Returns the search radius required for each sample point
    def search_radius(self) -> float:
        dx, dy = self.xy_dist()
        width = dx / math.ceil(dx / abs(self.resolution))
        height = dy / math.ceil(dy / abs(self.resolution))
        return Sample.bounding_radius(width, height)
          
    # Returns the average horizontal and vertical dimensions
    # of the bounding "rectangle" defined by two lat-lon coordinates
    def xy_dist(self) -> tuple[float, float]:
        dx = (distance.distance((self.p1[0], self.p1[1]), (self.p1[0], self.p2[1])).m +
            distance.distance((self.p2[0], self.p1[1]), (self.p2[0], self.p2[1])).m) / 2
        dy = (distance.distance((self.p1[0], self.p1[1]), (self.p2[0], self.p1[1])).m +
            distance.distance((self.p1[0], self.p2[1]), (self.p2[0], self.p2[1])).m) / 2
        return (dx, dy)
    
    # Returns an iterable with the minimum number of values
    # such that its values are at most max_dist apart
    # and the mean of the values is equal to the centre of start and end
    @staticmethod
    def generate_samples(start: float, end: float, max_dist: float) -> Generator[float, None, None]:
        d = end - start
        num = math.ceil(abs(d / max_dist))
        sample_dist = d / num
        return (start + (sample_dist / 2) + i * sample_dist for i in range(num))

    # Returns the radius of the smallest bounding circle
    # of a rectangle defined by width and height
    @staticmethod
    def bounding_radius(width: float, height: float) -> float:
        return math.sqrt((width * width + height * height) / 4)