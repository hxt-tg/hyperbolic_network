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
        static double distance(const HyperbolicPoint &p1, const HyperbolicPoint &p2, double zeta);
};


class HyperbolicRandomNet : public UndirectedNet
{
	public:
	    /* Default: zeta=1, beta=1.66, avg_degree=k=6, T=0.3, gamma=2.6 */
		explicit HyperbolicRandomNet(bool use_raw, int n_points, double alpha, double beta, double R, double zeta=1, int seed=-1);
		explicit HyperbolicRandomNet(int n_points, double e_gamma, double T, double e_degree, double zeta=1, int seed=-1);
		std::string details() const;
		std::string points_xy() const;
		std::string points_theta_r() const;
        HyperbolicPoint *get_points() {return points;}
        
	private:
	    double R;
	    double T;
	    double zeta;
	    double beta;
	    double alpha;
	    double e_gamma;
	    double e_degree;
	    int seed;
	    HyperbolicPoint *points;
	    
	    void build_net();
	    double pdf_r(double r) const;
        double rand_r() const;
        double rand_theta() const;
        double distance(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const;
        double prob_temperature(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const;
        double prob_heaviside(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const;
};

#endif
