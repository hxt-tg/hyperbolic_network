#include "coordinate.h"

/* CartesianPoint */

CartesianPoint::CartesianPoint(double x, double y){
    _x = x;
    _y = y;
}

double CartesianPoint::theta() const{
    if (fabs(_y) < 1e-7) 
        return (fabs(_x) < 1e-7) ? 0 : (_x < 0 ? M_PI : 0);    
    double a = acos(_x/r());
    return _y > 0 ? a : (M_PI*2 - a);
}

std::ostream &operator<<(std::ostream &out, const CartesianPoint &p){ 
    out << '(' << p._x << ", " << p._y << ')';
    return out;            
}

CartesianPoint CartesianPoint::operator+(const CartesianPoint &p) const{
    return CartesianPoint(_x + p._x, _y + p._y);
}

CartesianPoint CartesianPoint::operator-(const CartesianPoint &p) const{
    return CartesianPoint(_x - p._x, _y - p._y);
}

PolarPoint CartesianPoint::to_polar() const{
    return PolarPoint(theta(), r());
}

double CartesianPoint::angle(const CartesianPoint &p1, const CartesianPoint &p2){
    return fabs(p1.theta() - p2.theta());
}

double CartesianPoint::distance(const CartesianPoint &p1, const CartesianPoint &p2){
    return sqrt((p1._x-p2._x)*(p1._x-p2._x)+(p1._y-p2._y)*(p1._y-p2._y));
}

double CartesianPoint::dot(const CartesianPoint &p1, const CartesianPoint &p2){
    return p1.r() * p2.r() * cos(CartesianPoint::angle(p1, p2));
}


/* PolarPoint */

PolarPoint::PolarPoint(double theta, double r){
    _theta = theta;
    _r = r;
}

std::ostream &operator<<(std::ostream &out, const PolarPoint &p){ 
    out << "(theta=" << p._theta << ", r=" << p._r << ')';
    return out;            
}

PolarPoint PolarPoint::operator+(const PolarPoint &p) const{
    return CartesianPoint(x() + p.x(), y() + p.y()).to_polar();
}

PolarPoint PolarPoint::operator-(const PolarPoint &p) const{
    return CartesianPoint(x() - p.x(), y() - p.y()).to_polar();
}

CartesianPoint PolarPoint::to_cartesian() const {
    return CartesianPoint(x(), y());
}

double PolarPoint::angle(const PolarPoint &p1, const PolarPoint &p2){
    return fabs(p1._theta - p2._theta);
}

double PolarPoint::distance(const PolarPoint &p1, const PolarPoint &p2){
    return CartesianPoint::distance(p1.to_cartesian(), p2.to_cartesian());
}

double PolarPoint::dot(const PolarPoint &p1, const PolarPoint &p2){
    return p1._r * p2._r * cos(PolarPoint::angle(p1, p2));
}

