#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>
#include <cstdlib>
#include <iostream>


class PolarPoint;

class CartesianPoint
{
	public:
		CartesianPoint(double x=0, double y=0);
        double x() const{return _x;}
        double y() const{return _y;}
        double r() const{return sqrt(_x*_x + _y*_y);}
        double theta() const;
        friend std::ostream &operator<<(std::ostream &out, const CartesianPoint &p);
        CartesianPoint operator+(const CartesianPoint &p) const;
        CartesianPoint operator-(const CartesianPoint &p) const;
        PolarPoint to_polar() const;
        static double angle(const CartesianPoint &p1, const CartesianPoint &p2);
        static double distance(const CartesianPoint &p1, const CartesianPoint &p2);
        static double dot(const CartesianPoint &p1, const CartesianPoint &p2);      /* Dot Prouction */
	private:
	    double _x;
	    double _y;
};

class PolarPoint
{
	public:
		PolarPoint(double theta=0, double r=0);
        double r() const{return _r;}
        double theta() const{return _theta;}
        double x() const{return _r * cos(_theta);}
        double y() const{return _r * sin(_theta);}
        friend std::ostream &operator<<(std::ostream &out, const PolarPoint &p);
        PolarPoint operator+(const PolarPoint &p) const;
        PolarPoint operator-(const PolarPoint &p) const;
        CartesianPoint to_cartesian() const;
        static double angle(const PolarPoint &p1, const PolarPoint &p2);
        static double distance(const PolarPoint &p1, const PolarPoint &p2);
        static double dot(const PolarPoint &p1, const PolarPoint &p2);      /* Dot Prouction */
	private:
	    double _theta;
	    double _r;
};

#endif
