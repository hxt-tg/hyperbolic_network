#include "hyper.h"
#include "netlib/_exception.h"
#include "netlib/random.h" 

#include <iostream>
#include <sstream>
#include <cmath>

/* HyperbolicPoint */
HyperbolicPoint::HyperbolicPoint(double theta, double r)
:PolarPoint(theta, r){
    
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


/* HyperbolicRandomNet */
HyperbolicRandomNet::HyperbolicRandomNet(int n_points, double zeta, double beta, double R)
:UndirectedNet(n_points){
    if (zeta <= 0) throw NetException("Zeta should be larger than 0.");
    if (n_points < 0) throw NetException("Invalid points number.");
    this->R = R;
    this->zeta = zeta;
    this->beta = beta;
    double raw_zeta = HyperbolicPoint::getZeta();
    points = new HyperbolicPoint[totalVexNum()];
    for (int i = 0; i < totalVexNum(); i++)
        points[i] = HyperbolicPoint(randf()*2*M_PI,
                                    asinh((cosh(R)-1)*randf()));
    for (int i = 0; i < totalVexNum(); i++)
        for (int j = i+1; j < totalVexNum(); j++)
            if (randf() < 1/(exp(beta * zeta / 2 *
                    (HyperbolicPoint::distance(points[i], points[j])-R))+1))
                addLink(i, j);
    HyperbolicPoint::setZeta(raw_zeta);
}

HyperbolicRandomNet::HyperbolicRandomNet(int n_points, double zeta, double avg_degree, double T, double gamma)
:UndirectedNet(n_points){
    if (zeta <= 0) throw NetException("Zeta should be larger than 0.");
    if (n_points < 0) throw NetException("Invalid points number.");
    double gamma_temp = (gamma-1)*(gamma-1)/((gamma-2)*(gamma-2));
    this->R = 2 * log(2*T*n_points*gamma_temp/(avg_degree*sin(T*M_PI)));
    this->zeta = zeta;
    this->beta = 1.0/T;
    double raw_zeta = HyperbolicPoint::getZeta();
    points = new HyperbolicPoint[totalVexNum()];
    for (int i = 0; i < totalVexNum(); i++)
        points[i] = HyperbolicPoint(randf()*2*M_PI,
                                    log(randf())/(gamma/2-0.5)+R);
    for (int i = 0; i < totalVexNum(); i++)
        for (int j = i+1; j < totalVexNum(); j++)
            if (randf() < 1/(exp(beta * zeta / 2 *
                    (HyperbolicPoint::distance(points[i], points[j])-R))+1))
                addLink(i, j);
    HyperbolicPoint::setZeta(raw_zeta);
}

void HyperbolicRandomNet::printDetails(){
    std::cout << "R=" << R << ", zeta=" << zeta << ", beta=" << beta;
}

std::string HyperbolicRandomNet::pointsXYInfo(){
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].getX() << ',' << points[i].getY() << std::endl;
	return stream.str();
}

std::string HyperbolicRandomNet::pointsThetaRInfo(){
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].getTheta() << ',' << points[i].getR() << std::endl;
	return stream.str();
}
