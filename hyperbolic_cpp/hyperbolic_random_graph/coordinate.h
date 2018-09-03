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
        double getX() const{return x;}
        double getY() const{return y;}
        double getR() const{return sqrt(x*x + y*y);}
        double getTheta() const;
        friend std::ostream &operator<<(std::ostream &out, const CartesianPoint &p);
        CartesianPoint operator+(const CartesianPoint &p) const;
        CartesianPoint operator-(const CartesianPoint &p) const;
        PolarPoint toPolar() const;
        static double angle(const CartesianPoint &p1, const CartesianPoint &p2);
        static double distance(const CartesianPoint &p1, const CartesianPoint &p2);
        static double dot(const CartesianPoint &p1, const CartesianPoint &p2);      /* Dot Prouction */
	private:
	    double x;
	    double y;
};

class PolarPoint
{
	public:
		PolarPoint(double theta=0, double r=0);
        double getR() const{return r;}
        double getTheta() const{return theta;}
        double getX() const{return r * cos(theta);}
        double getY() const{return r * sin(theta);}
        friend std::ostream &operator<<(std::ostream &out, const PolarPoint &p);
        PolarPoint operator+(const PolarPoint &p) const;
        PolarPoint operator-(const PolarPoint &p) const;
        CartesianPoint toCartesian() const;
        static double angle(const PolarPoint &p1, const PolarPoint &p2);
        static double distance(const PolarPoint &p1, const PolarPoint &p2);
        static double dot(const PolarPoint &p1, const PolarPoint &p2);      /* Dot Prouction */
	private:
	    double theta;
	    double r;
};

#endif
