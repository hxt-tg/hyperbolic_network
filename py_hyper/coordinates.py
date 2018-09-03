from math import pi, sin, cos, acos, sqrt, sinh, cosh, acosh


class Cartesian:
    def __init__(self, x: float = 1, y: float = 0):
        self.__x = x
        self.__y = y
        
    def __str__(self):
        return '(' + str(self.__x) + ', ' + str(self.__y) + ')'
    
    def __add__(self, p):
        return Cartesian(self.x + p.x, self.y + p.y)
    
    def __sub__(self, p):
        return Cartesian(self.x - p.x, self.y - p.y)
    
    def __mul__(self, p) -> "Dot production":
        return self.r * p.r * cos(Cartesian.angle(self, p))
    
    @property
    def x(self):
        return self.__x
    
    @x.setter
    def x(self, value: float):
        self.__x = value
        
    @property
    def y(self):
        return self.__y
    
    @y.setter
    def y(self, value: float):
        self.__y = value
    
    @property
    def r(self) -> "float for distance between (0, 0)":
        return sqrt(self.__x**2 + self.__y**2)
    
    @property
    def theta(self) -> "float for angle between element vector (1, 0)":
        if self.__y == 0: return None if abs(self.__x - 0) < 1e-7 else (pi if self.__x < 0 else 0.0)
        a = acos(self.__x/self.r)
        return a if self.__y > 0 else (pi*2 - a)
    
    @staticmethod
    def angle(p1, p2):
        return abs(p1.theta - p2.theta)
    
    @staticmethod
    def distance(p1, p2):
        return sqrt((p1.x-p2.x)**2+(p1.y-p2.y)**2)

    def toPolar(self):
        return Polar(self.theta, self.r)
    

class Polar:
    def __init__(self, theta: float = 0, r: float = 1):
        self.__theta = theta % (2*pi)
        self.__r = r
        
    def __str__(self):
        return '(θ=' + str(self.__theta) + ', r=' + str(self.__r) + ')'
    
    def __add__(self, p):
        return Cartesian(self.x + p.x, self.y + p.y).toPolar()
    
    def __sub__(self, p):
        return Cartesian(self.x - p.x, self.y - p.y).toPolar()
    
    def __mul__(self, p) -> "Dot production":
        return self.r * p.r * cos(Polar.angle(self, p))
    
    @property
    def theta(self):
        return self.__theta
    
    @theta.setter
    def theta(self, value: float):
        self.__theta = value % (2*pi)
        
    @property
    def r(self):
        return self.__r
    
    @r.setter
    def y(self, value: float):
        self.__r = value
    
    @property
    def x(self):
        return self.__r * cos(self.__theta)
    
    @property
    def y(self):
        return self.__r * sin(self.__theta)

    @staticmethod
    def distance(p1, p2):
        return Cartesian.distance(p1.toCartesian(), p2.toCartesian())

    @staticmethod
    def angle(p1, p2):
        return abs(p1.theta - p2.theta)
    
    def toCartesian(self):
        return Cartesian(self.x, self.y)

    
class Hyperbolic(Polar):
    __zeta = 1

    def __init__(self, theta: float = 0, r: float = 1):
        Polar.__init__(self, theta, r)

    @classmethod
    def setZeta(cls, zeta: "Float > 0, equals to 1/R" = 1):
        if zeta <= 0: raise ValueError('Zeta should be larger than 0.')
        cls.__zeta = zeta
    
    @classmethod
    def getZeta(cls):
        return cls.__zeta
    
    @classmethod
    def distance(cls, p1, p2) -> "Hyperbolic distance":
        if p1 is p2: return 0
        return acosh(cosh(cls.__zeta * p1.r) * cosh(cls.__zeta * p2.r) -\
                     sinh(cls.__zeta * p1.r) * sinh(cls.__zeta * p2.r) *\
                     cos(pi-abs(pi-abs(p1.theta-p2.theta))))/cls.__zeta
        

# Unit test
if __name__=='__main__':
    a = Hyperbolic(-pi/6, 2)
    b = Hyperbolic(pi/6, 2)
    print(Hyperbolic.distance(a, b))
