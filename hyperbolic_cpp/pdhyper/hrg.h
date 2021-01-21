// Hyperbolic Random Graph
#ifndef PDHYPER_HRG_H
#define PDHYPER_HRG_H

#include "cimnet/_base_net.h"
#include "coordinate.h"

#include <vector>

typedef PolarPoint HyperbolicPoint;

class HyperbolicNet : public Network<> {
public:
    explicit HyperbolicNet(int n_points, double T = 0, double gamma = 2, double K = 10,
                           double zeta = 1, int S = 1, int I = 1)
            : Network<>() {
        this->T = T;
        this->gamma = gamma;
        this->K = K;
        this->zeta = zeta;
        this->S = S;
        this->I = I;
        this->points = new HyperbolicPoint[n_points];
        for (auto i = 0; i < n_points; i++)
            this->add_node(i);
    }

    ~HyperbolicNet() {
        delete this->points;
    }

    double distance(const HyperbolicPoint &p1, const HyperbolicPoint &p2) const {
        if (&p1 == &p2) return 0;
        return acosh(cosh(zeta * p1.getR()) * cosh(zeta * p2.getR()) -
                     sinh(zeta * p1.getR()) * sinh(zeta * p2.getR()) *
                     cos(M_PI - fabs(M_PI - fabs(p1.getTheta() - p2.getTheta()))) / zeta);

    }

    void setPoint(int idx, double theta, double r) {
        if (idx >= number_of_nodes()) throw NetworkException("Index out of range");
        points[idx].setTheta(theta);
        points[idx].setR(r);
    }

    /*
#define BUFSIZE 64
    static HyperbolicNet *read_hg(const char *hg_filename=NULL) {
        FILE *fp = stdin;
        if (hg_filename){
            fp = fopen(hg_filename, "r");
            if (!hg_filename) throw NetworkException("File not avaliable");
        }

        char _, buf[BUFSIZE], *b=buf, exit_flag = 0;  // Skipped char
        int N, S, I;
        double T, G, K, Z;
        fscanf(fp, "N\t%d\tT\t%lf\tG\t%lf\tK\t%lf\tZ\t%lf\tS\t%d\tI\t%d", &N, &T, &G, &K, &Z, &S, &I);
        HyperbolicNet *net = new HyperbolicNet(N, T, G, K, Z, S, I);
        for (int i = 0; i < N; i++){
            int id;
            double theta, r;
            fscanf(fp, "%d\t%lf\t%lf", &id, &r, &theta);
            net->setPoint(i, theta, r);
        }
        while (1){
            int x, y;
            while (1) {
                *b = fgetc(fp);
                if (*b == EOF) exit_flag = 1;
                if (*b == EOF || *b == '\n') break;
                b++;
            }
            *b++ = '\n';
            *b = 0;
            b = buf;
            sscanf(buf, "%d\t%d", &x, &y);
            net->addLink(x-I, y-I);
            if (exit_flag) break;
        }
        if (hg_filename) fclose(fp);
        return net;
    }
    */

    void printFormatHG() {
        printf("N\t%d\tT\t%.10lf\tG\t%.10lf\tK\t%.10lf\tZ\t%.10lf\tS\t%d\tI\t%d\n",
               number_of_nodes(), T, gamma, K, zeta, S, I);
        for (int i = 0; i < number_of_nodes(); i++)
            printf("%d\t%.10lf\t%.10lf\n", i + I, points[i].getR(), points[i].getTheta());
        // TODO: std::cout << links_csv('\t', I) << std::endl;
    }

    void printDetails() {
        std::cout << "N=" << number_of_nodes()
                  << ", T=" << T
                  << ", gamma=" << gamma
                  << ", K=" << K
                  << ", zeta=" << zeta
                  << ", S=" << S
                  << ", I=" << I << "." << std::endl;
    }

    std::string pointsXYInfo() {
        std::stringstream stream;
        for (int i = 0; i < number_of_nodes(); i++)
            stream << points[i].getX() << ',' << points[i].getY() << std::endl;
        return stream.str();
    }

    std::string pointsThetaRInfo() {
        std::stringstream stream;
        for (int i = 0; i < number_of_nodes(); i++)
            stream << points[i].getTheta() << ',' << points[i].getR() << std::endl;
        return stream.str();
    }

    HyperbolicPoint *getPoints() { return points; }

private:
    double T;       /* Temperature */
    double gamma;   /* Power-law */
    double K;       /* Average degree */
    double zeta;    /* Hyperbolic curvature */
    int S;          /* Random seed */
    int I;          /* Initial node id */
    HyperbolicPoint *points;
};

#endif //PDHYPER_HRG_H
