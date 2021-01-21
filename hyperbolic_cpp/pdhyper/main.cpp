#include <iostream>
#include "cimnet/network.h"
#include "coordinate.h"

int main() {
    PolarPoint pp(0, 2);
    CartesianPoint cp = pp.toCartesian();
    std::cout << cp.toPolar() << std::endl;
    std::cout << pp << std::endl;
    return 0;
}
