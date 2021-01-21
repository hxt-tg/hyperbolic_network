#pragma once
#ifndef PDHYPER_POLAR_POINT_H
#define PDHYPER_POLAR_POINT_H

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "cartesian_point.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

class CartesianPoint;

class PolarPoint {
    friend std::ostream &operator<<(std::ostream &out, const PolarPoint &p) {
        out << "PolarPoint(theta=" << p.theta << ", r=" << p.r << ')';
        return out;
    }

public:
    explicit PolarPoint(double theta = 0, double r = 0) {
        this->theta = theta;
        this->r = r;
    }

    void setTheta(double _theta) { this->theta = _theta; }

    void setR(double _r) { this->r = _r; }

    double getTheta() const { return theta; }

    double getR() const { return r; }

    double getX() const { return r * cos(theta); }

    double getY() const { return r * sin(theta); }

    PolarPoint operator+(const PolarPoint &p) const {
        return CartesianPoint(getX() + p.getX(), getY() + p.getY()).toPolar();
    }

    PolarPoint operator-(const PolarPoint &p) const {
        return CartesianPoint(getX() - p.getX(), getY() - p.getY()).toPolar();
    }

    CartesianPoint toCartesian() const;

    static double angle(const PolarPoint &p1, const PolarPoint &p2) {
        return fabs(p1.theta - p2.theta);
    }

    static double distance(const PolarPoint &p1, const PolarPoint &p2) {
        return CartesianPoint::distance(p1.toCartesian(), p2.toCartesian());
    }

    static double dot(const PolarPoint &p1, const PolarPoint &p2) {
        return p1.r * p2.r * cos(PolarPoint::angle(p1, p2));
    }

private:
    double theta;
    double r;
};

#endif //PDHYPER_POLAR_POINT_H
