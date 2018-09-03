from random import random, randint

# Net generation part

class HyperNet:
    def __init__(self, total_nodes):
        if isinstance(total_nodes, int):
            self._players = [i+1 for i in range(total_nodes)]
        else:
            raise ValueError('Parameters should be int.')
        self._links = {}
    
    def __str__(self):
        nm = self.neighborsMatrix()
        s = ""
        for i in range(0, len(nm)):
            s += str(i+1) + ": " + str(nm[i]) + "\n"
        return s
    
    def _getPair(self, p1, p2):
        if p1 < 0 or p1 > len(self._players)-1 or \
           p2 < 0 or p2 > len(self._players)-1:
            raise ValueError('ID out of range.')
        if p1 == p2: raise ValueError('Should link two different point.')
        if p1 > p2: p1, p2 = p2, p1
        return (p1, p2)
    
    def totalNodesNum(self):
        return len(self._players)
    
    def totalLinksNum(self):
        return len(self._links)
    
    def totalDegree(self):
        return self.totalLinksNum()*2
    
    def averageDegree(self):
        return self.totalDegree()/self.totalNodesNum()
    
    def isLinked(self, p1, p2):
        pair = self._getPair(p1, p2)
        return pair in self._links
    
    def neighbors(self, p):
        if p < 0 or p > len(self._players)-1:
            raise ValueError('ID out of range.')
        nei = []
        for l in self._links.keys():
            if p in l: nei.append(l[1] if l[0] == p else l[0])
        return nei
    
    def neighborsMatrix(self):
        m = []
        for p in self._players:
            m.append(self.neighbors(p))
        return m
    
    def removeLink(self, p1, p2):
        pair = self._getPair(p1, p2)
        if pair in self._links:
            del self._links[pair]
        
    def addLink(self, p1, p2, weight=1):
        if weight == 0: self.removeLink(p1, p2)
        pair = self._getPair(p1, p2)
        self._links[pair] = weight
    
    def getAllLinks(self):
        return self._links.copy()
