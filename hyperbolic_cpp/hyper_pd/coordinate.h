#ifndef COORDINATE_H
#define COORDINATE_H

#include <cstdlib>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

class PolarPoint;

class CartesianPoint
{
	public:
		CartesianPoint(double x=0, double y=0);
		void setX(double x) {this->x = x;}
        void setY(double y) {this->y = y;}
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
		void setTheta(double theta) {this->theta = theta;}
		void setR(double r) {this->r = r;}
        double getTheta() const{return theta;}
        double getR() const{return r;}
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
