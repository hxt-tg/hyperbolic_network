#pragma once
#ifndef PDHYPER_CARTESIAN_POINT_H
#define PDHYPER_CARTESIAN_POINT_H

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "polar_point.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

class PolarPoint;

class CartesianPoint {
    friend std::ostream &operator<<(std::ostream &out, const CartesianPoint &p) {
        out << "CartesianPoint(x=" << p.x << ", y=" << p.y << ')';
        return out;
    }

public:
    explicit CartesianPoint(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }

    void setX(double _x) { this->x = _x; }

    void setY(double _y) { this->y = _y; }

    double getX() const { return x; }

    double getY() const { return y; }

    double getR() const { return sqrt(x * x + y * y); }

    double getTheta() const {
        if (fabs(y) < 1e-7)
            return (fabs(x) < 1e-7) ? 0 : (x < 0 ? M_PI : 0);
        double a = acos(x / getR());
        return y > 0 ? a : (M_PI * 2 - a);
    }

    CartesianPoint operator+(const CartesianPoint &p) const {
        return CartesianPoint(x + p.x, y + p.y);
    }

    CartesianPoint operator-(const CartesianPoint &p) const {
        return CartesianPoint(x - p.x, y - p.y);
    }

    PolarPoint toPolar() const;

    static double angle(const CartesianPoint &p1, const CartesianPoint &p2) {
        return fabs(p1.getTheta() - p2.getTheta());
    }

    static double distance(const CartesianPoint &p1, const CartesianPoint &p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    static double dot(const CartesianPoint &p1, const CartesianPoint &p2) {
        return p1.getR() * p2.getR() * cos(CartesianPoint::angle(p1, p2));
    }

private:
    double x;
    double y;
};

#endif //PDHYPER_CARTESIAN_POINT_H
