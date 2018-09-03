#include "hypernet.h"
#include "netlib/_exception.h"
#include "netlib/random.h" 

#include <sstream>
#include <cstdio>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/* HyperbolicPoint */
HyperbolicPoint::HyperbolicPoint(double theta, double r)
: PolarPoint(theta, r){
    
}

double HyperbolicPoint::zeta = 1;
double HyperbolicPoint::distance(const HyperbolicPoint &p1, const HyperbolicPoint &p2){
    if (&p1 == &p2) return 0;
    return acosh(cosh(zeta * p1.getR()) * cosh(zeta * p2.getR()) -
                 sinh(zeta * p1.getR()) * sinh(zeta * p2.getR()) *
                 cos(M_PI-fabs(M_PI-fabs(p1.getTheta()-p2.getTheta())))/zeta);
}

void HyperbolicPoint::setZeta(double zeta){
    HyperbolicPoint::zeta = zeta;
}

double HyperbolicPoint::getZeta(){
    return zeta;
}


/* HyperbolicNet */
HyperbolicNet::HyperbolicNet(int n_points, double T, double gamma, double K, 
                             double zeta, int S, int I)
: UndirectedNet(n_points){
    this->T = T;
    this->gamma = gamma;
    this->K = K;
    this->zeta = zeta;
    this->S = S;
    this->I = I;
    this->points = new HyperbolicPoint[n_points];
}

HyperbolicNet::~HyperbolicNet(){
    delete this->points;
}

void HyperbolicNet::setPoint(int idx, double theta, double r){
    if (idx >= totalVexNum()) throw NetException("Index out of range");
    points[idx].setTheta(theta);
    points[idx].setR(r);
}

HyperbolicNet *HyperbolicNet::read_hg(){
    char _;  /* Skipped char */
    int N, S, I;
    double T, G, K, Z;
    scanf("N\t%d\tT\t%lf\tG\t%lf\tK\t%lf\tZ\t%lf\tS\t%d\tI\t%d", &N, &T, &G, &K, &Z, &S, &I);
    HyperbolicNet *net = new HyperbolicNet(N, T, G, K, Z, S, I);
    for (int i = 0; i < N; i++){
        int id;
        double theta, r;
        scanf("%d\t%lf\t%lf", &id, &r, &theta);
        net->setPoint(i, theta, r);
    }
    while (!feof(stdin)){
        int a, b;
        scanf("%d\t%d", &a, &b);
        net->addLink(a-I, b-I);
    }
    return net;
}

void HyperbolicNet::printFormatHG(){
    printf("N\t%d\tT\t%.10lf\tG\t%.10lf\tK\t%.10lf\tZ\t%.10lf\tS\t%d\tI\t%d\n", 
           totalVexNum(), T, gamma, K, zeta, S, I);
    for (int i = 0; i < totalVexNum(); i++)
        printf("%d\t%.10lf\t%.10lf\n", i+I, points[i].getR(), points[i].getTheta());
    std::cout << links_csv('\t', I) << std::endl;
}

void HyperbolicNet::printDetails(){
    std::cout << "N="       << totalVexNum() 
              << ", T="     << T
              << ", gamma=" << gamma
              << ", K="     << K
              << ", zeta="  << zeta
              << ", S="     << S
              << ", I="     << I << "." << std::endl;
}

std::string HyperbolicNet::pointsXYInfo(){
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].getX() << ',' << points[i].getY() << std::endl;
	return stream.str();
}

std::string HyperbolicNet::pointsThetaRInfo(){
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].getTheta() << ',' << points[i].getR() << std::endl;
	return stream.str();
}


