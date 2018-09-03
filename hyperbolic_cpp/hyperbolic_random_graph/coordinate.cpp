#include "coordinate.h"

/* CartesianPoint */

CartesianPoint::CartesianPoint(double x, double y){
    this->x = x;
    this->y = y;
}

double CartesianPoint::getTheta() const{
    if (fabs(y) < 1e-7) 
        return (fabs(x) < 1e-7) ? 0 : (x < 0 ? M_PI : 0);    
    double a = acos(x/getR());
    return y > 0 ? a : (M_PI*2 - a);
}

std::ostream &operator<<(std::ostream &out, const CartesianPoint &p){ 
    out << '(' << p.x << ", " << p.y << ')';
    return out;            
}

CartesianPoint CartesianPoint::operator+(const CartesianPoint &p) const{
    return CartesianPoint(x + p.x, y + p.y);
}

CartesianPoint CartesianPoint::operator-(const CartesianPoint &p) const{
    return CartesianPoint(x - p.x, y - p.y);
}

PolarPoint CartesianPoint::toPolar() const{
    return PolarPoint(getTheta(), getR());
}

double CartesianPoint::angle(const CartesianPoint &p1, const CartesianPoint &p2){
    return fabs(p1.getTheta() - p2.getTheta());
}

double CartesianPoint::distance(const CartesianPoint &p1, const CartesianPoint &p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double CartesianPoint::dot(const CartesianPoint &p1, const CartesianPoint &p2){
    return p1.getR() * p2.getR() * cos(CartesianPoint::angle(p1, p2));
}


/* PolarPoint */

PolarPoint::PolarPoint(double theta, double r){
    this->theta = theta;
    this->r = r;
}

std::ostream &operator<<(std::ostream &out, const PolarPoint &p){ 
    out << "(theta=" << p.theta << ", r=" << p.r << ')';
    return out;            
}

PolarPoint PolarPoint::operator+(const PolarPoint &p) const{
    return CartesianPoint(getX() + p.getX(), getY() + p.getY()).toPolar();
}

PolarPoint PolarPoint::operator-(const PolarPoint &p) const{
    return CartesianPoint(getX() - p.getX(), getY() - p.getY()).toPolar();
}

CartesianPoint PolarPoint::toCartesian() const{
    return CartesianPoint(getX(), getY());
}

double PolarPoint::angle(const PolarPoint &p1, const PolarPoint &p2){
    return fabs(p1.theta - p2.theta);
}

double PolarPoint::distance(const PolarPoint &p1, const PolarPoint &p2){
    return CartesianPoint::distance(p1.toCartesian(), p2.toCartesian());
}

double PolarPoint::dot(const PolarPoint &p1, const PolarPoint &p2){
    return p1.r * p2.r * cos(PolarPoint::angle(p1, p2));
}

