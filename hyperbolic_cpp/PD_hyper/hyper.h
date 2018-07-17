#ifndef HYPER_H
#define HYPER_H

#include "netlib/_ud_net.h"
#include "coordinate.h"

#include <vector>

#define PPoint PolarPoint
#define CPoint CartesianPoint
#define HPoint HyperbolicPoint


class HyperbolicPoint : public PolarPoint
{
    public:
        explicit HyperbolicPoint(double theta=0, double r=0);
        static double distance(const HyperbolicPoint &p1, const HyperbolicPoint &p2);
        static void setZeta(double zeta);
        static double getZeta();
    private:
        static double zeta;
};


class HyperbolicRandomNet : public UndirectedNet
{
	public:
	    /* Default: zeta=1, beta=1.66, avg_degree=k=6, T=0.3, gamma=2.6 */
		explicit HyperbolicRandomNet(int n_points, double zeta, double beta, double R);
		explicit HyperbolicRandomNet(int n_points, double zeta, double avg_degree, double T, double gamma);
		void printDetails();
		std::string pointsXYInfo();
		std::string pointsThetaRInfo();
	private:
		void prod();
	    double R;
	    double zeta;
	    double beta;
	    HyperbolicPoint *points;
};

#endif
