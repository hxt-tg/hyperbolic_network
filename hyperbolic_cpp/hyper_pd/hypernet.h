#ifndef HYPERNET_H
#define HYPERNET_H

#include "netlib/_ud_net.h"
#include "coordinate.h"

#include <vector>

#define PPoint   PolarPoint
#define CPoint   CartesianPoint
#define HPoint   HyperbolicPoint
#define HyperNet HyperbolicNet


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

class HyperbolicNet : public UndirectedNet
{
    public:
        explicit HyperbolicNet(int n_points, double T=0, double gamma=2, double K=10, 
                               double zeta=1, int S=1, int I=1);
        ~HyperbolicNet();
        void setPoint(int idx, double theta, double r);
        static HyperbolicNet *read_hg(const char *hg_filename=NULL);
        void printFormatHG();
        void printDetails();
        std::string pointsXYInfo();
        std::string pointsThetaRInfo();
        HyperbolicPoint *getPoints(){return points;}
    private:
        double T;       /* Temperature */
        double gamma;   /* Power-law */
        double K;       /* Average degree */ 
        double zeta;    /* Hyperbolic curvature */
        int S;          /* Random seed */
        int I;          /* Initial node id */
        HyperbolicPoint *points;
};

#endif
