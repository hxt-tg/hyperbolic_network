import matplotlib.pyplot as plt
from math import *
from random import random
from coordinates import Hyperbolic


def read(fnet, fpoints):
    points = []
    links = []
    with open(fpoints) as f:
        for line in f.read().strip().split('\n'):
            points.append(Hyperbolic(*list(map(float, line.split(',')))))
    with open(fnet) as f:
        for line in f.read().strip().split('\n'):
            links.append(tuple(map(int, line.split(','))))
    return points, links


def draw(links, points, linecolor='b', dotcolor='k', linewidth=0.25,
         markersize=2, large_markersize=5, large_dotcolor='r'):
    x = []
    y = []
    for p in points:
        x.append(p.x)
        y.append(p.y)
    for i, (p1, p2) in enumerate(links):
        if i % 100 == 0: print('{:2f}%'.format(i/len(links)*100))
        plt.plot([points[p1].x, points[p2].x], [points[p1].y, points[p2].y],
                 linecolor + '-', linewidth=linewidth)
    plt.plot(x, y, dotcolor + '.', ms=markersize)


plt.subplot(331)
points, links = read('net.0.3.csv', 'points.0.3.csv')
draw(links, points)

plt.subplot(332)
points, links = read('net.0.35.csv', 'points.0.35.csv')
draw(links, points)

plt.subplot(333)
points, links = read('net.0.4.csv', 'points.0.4.csv')
draw(links, points)

plt.subplot(334)
points, links = read('net.0.45.csv', 'points.0.45.csv')
draw(links, points)

plt.subplot(335)
points, links = read('net.0.5.csv', 'points.0.5.csv')
draw(links, points)

plt.subplot(336)
points, links = read('net.0.55.csv', 'points.0.55.csv')
draw(links, points)

plt.subplot(337)
points, links = read('net.0.6.csv', 'points.0.6.csv')
draw(links, points)

plt.subplot(338)
points, links = read('net.0.65.csv', 'points.0.65.csv')
draw(links, points)

plt.subplot(339)
points, links = read('net.0.7.csv', 'points.0.7.csv')
draw(links, points)

plt.show()
