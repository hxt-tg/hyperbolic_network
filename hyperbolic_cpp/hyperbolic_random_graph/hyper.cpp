#include "hyper.h"
#include "netlib/_exception.h"
#include "netlib/random.h" 

#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>

#define MAX_GAMMA 10
#define MAX_TEMP  10

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/* HyperbolicPoint */
HyperbolicPoint::HyperbolicPoint(double theta, double r)
:PolarPoint(theta, r) {
}

double HyperbolicPoint::distance
(const HyperbolicPoint &p1, const HyperbolicPoint &p2, double zeta) {
    if (&p1 == &p2) return 0;
    return acosh(cosh(zeta * p1.r()) * cosh(zeta * p2.r()) -
                 sinh(zeta * p1.r()) * sinh(zeta * p2.r()) *
                 cos(M_PI-fabs(M_PI-fabs(p1.theta()-p2.theta()))))/zeta;
}


/* HyperbolicRandomNet */
HyperbolicRandomNet::HyperbolicRandomNet
(bool use_raw, int n_points, double alpha, double beta, double R, double zeta, int seed)
:UndirectedNet(n_points) {
    if (zeta <= 0) throw NetException("Zeta should be larger than 0.");
    this->seed = seed == -1 ? time((time_t *) NULL) : seed;
    this->zeta = zeta;
    
    this->beta = beta;
    this->T = 1 / beta;
    
    this->alpha = alpha;
    this->e_gamma = 2 * alpha / zeta * (T > 1 ? T : 1) + 1;
    
    this->R = R;
    this->e_degree = 0; /* TODO */
    
    build_net();
}


HyperbolicRandomNet::HyperbolicRandomNet
(int n_points, double e_gamma, double T, double e_degree, double zeta, int seed)
:UndirectedNet(n_points) {
    if (zeta <= 0) throw NetException("Zeta should be larger than 0.");
    this->seed = seed == -1 ? time((time_t *) NULL) : seed;
    this->zeta = zeta;
    
    this->T = T;
    this->beta = 1 / T;
    
    this->e_gamma = e_gamma;
    this->alpha = 0; /* TODO */
    
    this->R = 0; /* TODO */
    this->e_degree = e_degree;
    
    build_net();
}

void HyperbolicRandomNet::build_net() {
    points = new HyperbolicPoint[totalVexNum()];
    sgenrand((unsigned long)seed);
    /* Distribute points */
    for (int i = 0; i < totalVexNum(); i++)
        points[i] = HyperbolicPoint(rand_theta(), rand_r());
    /* Distribute links */
    if (fabs(T) < 1e-7)
        for (int i = 0; i < totalVexNum(); i++)
            for (int j = i+1; j < totalVexNum(); j++)
                if (randf() < prob_heaviside(points[i], points[j]))
                    addLink(i, j);
    else
        for (int i = 0; i < totalVexNum(); i++)
            for (int j = i+1; j < totalVexNum(); j++)
                if (randf() < prob_temperature(points[i], points[j]))
                    addLink(i, j);
}

std::string HyperbolicRandomNet::details() const {
    std::stringstream stream;
    stream << UndirectedNet::details()
           << "| > zeta=" << zeta << ", gamma=" << e_gamma << ", T=" << T << ", R=" << R << std::endl;
	stream << "+------------------------------- Hyperbolic RGG ------------------------------+\n";
	return stream.str();
}

std::string HyperbolicRandomNet::points_xy() const {
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].x() << ',' << points[i].y() << std::endl;
	return stream.str();
}

std::string HyperbolicRandomNet::points_theta_r() const {
    std::stringstream stream;
	for (int i = 0; i < totalVexNum(); i++)
		stream << points[i].theta() << ',' << points[i].r() << std::endl;
	return stream.str();
}

/* Private funcs */
double HyperbolicRandomNet::pdf_r(double r) const {
    return alpha * sinh(alpha * r)/(cosh(alpha * R) - 1);
}

double HyperbolicRandomNet::rand_r() const {
    return 1 / alpha * acosh(1 + cosh(alpha * R) * randf());
}

double HyperbolicRandomNet::rand_theta() const {
    return 2 * M_PI * randf();
}

double HyperbolicRandomNet::distance
(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const {
    if (&p1 == &p2) return 0;
    return acosh(cosh(zeta * p1.r()) * cosh(zeta * p2.r()) -
                 sinh(zeta * p1.r()) * sinh(zeta * p2.r()) *
                 cos(M_PI-fabs(M_PI-fabs(p1.theta()-p2.theta()))))/zeta;
}

double HyperbolicRandomNet::prob_temperature
(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const {
    return 1/(1 + exp(beta * zeta / 2 * (distance(p1, p2) - R)));
}

double HyperbolicRandomNet::prob_heaviside
(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const {
    return distance(p1, p2) > R ? 1 : 0;
}

