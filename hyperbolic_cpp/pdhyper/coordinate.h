#ifndef PDHYPER_COORDINATE_H
#define PDHYPER_COORDINATE_H

#include "polar_point.h"
#include "cartesian_point.h"

CartesianPoint PolarPoint::toCartesian() const {
    return CartesianPoint(getX(), getY());
}

PolarPoint CartesianPoint::toPolar() const {
    return PolarPoint(getTheta(), getR());
}

#endif //PDHYPER_COORDINATE_H
