#include <iostream>
#include "hypernet.h"


int main(int argc, char** argv) {
    HyperbolicNet *net = HyperbolicNet::read_hg();
    //std::cout << net->pointsThetaRInfo();
    net->printFormatHG();
    return 0;
}


