import matplotlib.pyplot as plt
from scipy.optimize import fmin
from math import *
from random import random
from coordinates import Hyperbolic
from net import HyperNet

T = 0.8
GAMMA = 2.2
BETA = 1/(GAMMA-1)
R = 0
ZETA = 1


def read_links_csv(filename, size):
    net = HyperNet(size)
    with open(filename) as f:
        for i, j in list(map(lambda x: list(map(int, x.strip().split(','))), f.read().strip().split('\n'))):
            net.addLink(i, j)
    return net


def log_likelihood(a, points, pl, net):
    result = 0
    r = log(len(points)+1)
    for idx, p in enumerate(points):
        dis = acosh(cosh(p.r)*cosh(r) - sinh(p.r)*sinh(r)*cos(pi-fabs(pi-fabs(p.theta-a))))
        prob = 1/(1+exp((dis-R)/T))
        if fabs(prob) < 1e-7: prob = 1e-7
        if fabs(prob-1) < 1e-7: prob = 1 - 1e-7
        if net.isLinked(pl[len(points)], pl[idx]):
            result += log(prob)
        else:
            result += log(1-prob)
    return -result


def hypermap(net: HyperNet):
    global R
    hyper_points = [Hyperbolic(random()*2*pi, 0)]
    d_list = sorted([(i, len(net.neighbors(i))) for i in range(net.totalNodesNum())], key=lambda x: x[1], reverse=True)
    pl = [a[0] for a in d_list]     # point map list
    # m = d_list[-1][1]
    m = 2
    L = net.averageDegree()/2 - m
    t = net.totalNodesNum() + 1
    for i in range(2, net.totalNodesNum()+1):
        for j in range(i-1):
            hyper_points[j] = Hyperbolic(hyper_points[j].theta, BETA * log(j+1) + (1-BETA)*log(i))
        # Calculate R
        Ii = 1 / (1 - BETA) * (1 - i**(BETA-1))
        Li = 2*L*(1-BETA)/(1-t**(-(1-BETA)**2)*(2*BETA-1))*((t/i)**(2*BETA-1)-1)*(1-i**(BETA-1))
        Mi = m + Li
        R = log(i) - 2/ZETA*log(2*T*Ii/(sin(T*pi)*Mi))
        ai = fmin(log_likelihood, [random()*2*pi], args=(hyper_points, pl, net))
        hyper_points.append(Hyperbolic(ai, log(i)))
        print(i)
    return hyper_points, pl


def draw(p_list, pl, net, linecolor='k', dotcolor=(1, 0.7, 0, 1), linewidth=0.25,
                    markersize=2, large_markersize=5, large_dotcolor='r', show_large=False):
    x = []
    y = []
    large_x = []
    large_y = []
    for p in p_list:
        x.append(p.x)
        y.append(p.y)
    if show_large:
        for p in p_list[:int(len(p_list) * 0.05)]:
            large_x.append(p.x)
            large_y.append(p.y)
    for i in range(len(p_list)):
        for j in range(i+1, len(p_list)):
            if net.isLinked(pl[i], pl[j]):
                plt.plot([p_list[i].x, p_list[j].x], [p_list[i].y, p_list[j].y],
                         linecolor + '-', linewidth=linewidth, alpha=0.1)
    plt.plot(x, y, '.', ms=markersize, mfc=dotcolor)
    if show_large:
        plt.plot(large_x, large_y, large_dotcolor + '.', ms=large_markersize)
    plt.show()


net = read_links_csv('sf300.csv', 300)
point_list, pl = hypermap(net)
draw(point_list, pl, net)


