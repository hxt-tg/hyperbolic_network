import matplotlib.pyplot as plt
from math import *
import numpy as np
from random import random
from coordinates import *
import matplotlib
matplotlib.pyplot.switch_backend('Qt5Agg')


class HyperbolicRandomGraph:
    def __init__(self, zeta: float, T: float, maxR: float):
        if zeta <= 0: raise ValueError('Zeta should be larger than 0.')
        self.__zeta = zeta
        self.__T = T
        self.__max_r = maxR
    
    @property
    def zeta(self):
        return self.__zeta
    
    @zeta.setter
    def zeta(self, value: float):
        self.__zeta = value
    
    def generate_points(self, total_amount):
        raw_zeta = Hyperbolic.getZeta()
        if total_amount < 0: raise ValueError('In valid points number.')
        self.__points = []
        self.__links = []
        self.__link_pairs = []
        for i in range(total_amount):
            self.__points.append(Hyperbolic(random()*2*pi,
                                    asinh((cosh(self.__max_r)-1)*random())))
        Hyperbolic.setZeta(self.__zeta)
        p = self.__points
        for i in range(len(p)):
            for j in range(i+1, len(p)):
#                if random()<1/(exp(0.83*(Hyperbolic.distance(p[i],
#                                                             p[j]) - self.__max_r))):
                 if Hyperbolic.distance(p[i], p[j]) < self.__max_r:
                    self.__links.append((p[i], p[j]))
                    self.__link_pairs.append((i, j))
        Hyperbolic.setZeta(raw_zeta)
        self.__degrees = dict([[i, 0] for i in range(len(p))])
        for p1, p2 in self.__link_pairs:
            self.__degrees[p1] += 1
            self.__degrees[p2] += 1
    
    def draw(self, linecolor='k', dotcolor='k', linewidth=0.25,
                    markersize=2, large_markersize=5, large_dotcolor='r'):
        x = []
        y = []
        large_x = []
        large_y = []
        for p in self.__points:
            x.append(p.x)
            y.append(p.y)
        d = self.__degrees.items()
        for i, n in sorted(d, key=lambda x: x[1], reverse=True)[:int(len(d)*0.05)]:
            large_x.append(self.__points[i].x)
            large_y.append(self.__points[i].y)
        for p1, p2 in self.__links:
            plt.plot([p1.x, p2.x], [p1.y, p2.y], linecolor+'-', linewidth = linewidth)
        plt.plot(x, y, dotcolor + '.', ms = markersize)
        #plt.plot(large_x, large_y, large_dotcolor + '.', ms = large_markersize)
        plt.show()
        
    def draw_degree_distribution(self):
        d = list(filter(lambda x: x > 0, self.__degrees.values()))
        degree = {}
        for i in d:
            if i not in degree:
                degree[i] = 0
            degree[i] += 1
        x = degree.keys()
        y = degree.values()
        with open('degree.txt', 'w') as f:
            for k in degree:
                f.write('{},{}\n'.format(k, degree[k]))
        plt.plot(x, y, 'r.', ms = 4)
        plt.xscale('log')
        plt.yscale('log')
        plt.show()
        
hrg = HyperbolicRandomGraph(1, 0, 15)
hrg.generate_points(740)
hrg.draw()
#hrg.draw_degree_distribution()
