#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cfloat>
#include <limits>
#include "hypernet.h"
#include "coordinate.h"
#include "netlib/random.h"
#include "netlib/common_net.h"

#define RANGE_ERROR 126
#define MAX_R DBL_MAX 
#define _swap(x, y) do{ \
    auto t = y; \
    y = x; \
    x = t; \
} while(0);




using namespace std;

#define RANDOMIZE   3145215
#define SIZE        20000
#define REFRESH_FRE 50
#define K           0.1
#define MC_STEPS    10000
#define REC_STEPS   5000
#define TRY_TIMES   10

#define METRIC_CLUSTER

double gamma, beta, T, S, theta, r;
HyperbolicNet *net;

typedef enum {
    STRA_C = 0,
    STRA_D = 1
} Strategy;

int stra_cnt[2];
int stra[SIZE];
double payoff_matrix[2][2] = {{1, S},
                              {T, 0}};
#define update_matrix(T, S) do{\
    payoff_matrix[0][1]=S;\
    payoff_matrix[1][0]=T;\
}while(0)


typedef struct SMetric{
    double sr;      /* Start r */
    double er;      /* End r */
    double st;      /* Start theta */
    double et;      /* End theta */
    Strategy stra;  /* Select strategy */
} Metric;

typedef struct SMetricPercent{
    double percent; /* Percent of points, in [0, 1]. */
    double st;      /* Start theta */
    double et;      /* End theta */
    Strategy stra;  /* Select strategy */
} MetricPercent;

#ifdef METRIC_CLUSTER
void metric_cluster_stra(vector<Metric> &metric, Strategy default_stra){
    for (int i = 0; i < SIZE; i++)
        stra[i] = default_stra;
    HyperbolicPoint *points = net->getPoints();
    for (int j = 0; j < metric.size(); j++){
        if (metric[j].st < 0 || metric[j].st > 2*M_PI ||
           metric[j].et < 0 || metric[j].et > 2*M_PI){
            fprintf(stderr, "Metric value out of range.\n");
            exit(RANGE_ERROR);
        }
        if (metric[j].st > metric[j].et) _swap(metric[j].st, metric[j].et);
        for (int i = 0; i < net->totalVexNum(); i++){
            if (points[i].getR() < metric[j].sr || points[i].getR() > metric[j].er) continue;
            if (points[i].getTheta() < metric[j].st || points[i].getTheta() > metric[j].et) continue;
            stra[i] = metric[j].stra;
        }
    }
    stra_cnt[0] = stra_cnt[1] = 0;
    for (int i = 0; i < SIZE; i++)
        stra_cnt[stra[i]]++;
}

bool _cmp(HyperbolicPoint i,HyperbolicPoint j) { return (i.getR()<j.getR()); }

void metric_cluster_stra_by_percent(vector<MetricPercent> &metric, Strategy default_stra){
    vector<Metric> target_metric;
    for (int j = 0; j < metric.size(); j++){
        if (metric[j].percent < 0 || metric[j].percent > 1 ||
           metric[j].st < 0 || metric[j].st > 2*M_PI ||
           metric[j].et < 0 || metric[j].et > 2*M_PI){
            fprintf(stderr, "Metric value out of range.\n");
            exit(RANGE_ERROR);
        }
        if (metric[j].st > metric[j].et) _swap(metric[j].st, metric[j].et);
        if (fabs(metric[j].percent) < 1e-7){
            target_metric.push_back({0, 0, metric[j].st, metric[j].et, metric[j].stra});
            continue;
        }
        vector<HyperbolicPoint> hps;
        HyperbolicPoint *pts = net->getPoints();
        double end_r;
        for (int i = 0; i < net->totalVexNum(); i++)
            if (pts[i].getTheta() > metric[j].st && pts[i].getTheta() < metric[j].et)
                hps.push_back(pts[i]);
        sort (hps.begin(), hps.end(), _cmp);
        
        if (metric[j].percent > (double)hps.size()/net->totalVexNum()){
            fprintf(stdout, "Warning: The No.%d cluster percentage(%g) is larger than the points between (%g, %g). (%d/%d=%g < %g)\n",
                j+1, metric[j].percent, metric[j].st, metric[j].et, hps.size(), net->totalVexNum(), 
                (double)hps.size()/net->totalVexNum(), metric[j].percent);
            end_r = MAX_R;
        } else 
            end_r = hps[(metric[j].percent * net->totalVexNum())-1].getR();
        target_metric.push_back({0, end_r, metric[j].st, metric[j].et, metric[j].stra});
    }
    metric_cluster_stra(target_metric, default_stra);
}

void init_by_metric_cluster(){
    MetricPercent m0 = {r, 0, theta*M_PI, STRA_C};
    vector<MetricPercent> metric;
    metric.push_back(m0);
    metric_cluster_stra_by_percent(metric, STRA_D);
    // Metric m0 = {0, r, 0, theta*M_PI, STRA_C};
    // vector<Metric> metric;
    // metric.push_back(m0);
    // metric_cluster_stra(metric, STRA_D);
}
#endif

void init(){
    stra_cnt[0] = stra_cnt[1] = 0;
    for (int i = 0; i < SIZE; i++)
    	stra_cnt[stra[i] = randi(2)]++;
}

double payoff(int x){
	double p = 0;
	NeiArr xnei = net->getNeighbors(x);
	for (int i = 0; i < net->vexDegree(x); i++)
		p += payoff_matrix[stra[x]][stra[xnei[i]]];
	return p;
}

void update_stra(int x){
    if (net->vexDegree(x) == 0) return ;
    NeiArr xnei = net->getNeighbors(x);
    int y = xnei[(int)randi(net->vexDegree(x))];
    /* Update strategy, if same then exit */
    if (stra[x] == stra[y]) return ;
    if (randf() < 1/(1+exp((payoff(x) - payoff(y))/K))){
        stra_cnt[stra[x]]--;
        stra[x] = stra[y];
        stra_cnt[stra[x]]++;
    }
}

void createNetFromFile_FunctionTest(){
    HyperbolicNet *n = HyperbolicNet::read_hg();
    cout << "[Show theta, r data]" << endl;
    cout << n->pointsThetaRInfo();
    cout << "[Show linking details]" << endl;
    cout << n->links_csv() << endl;
    cout << "[Recreate hg file]" << endl;
    n->printFormatHG();
    delete n;
}

int main(int argc, char** argv) {
    //createNetFromFile_FunctionTest();
    ofstream file_aver, file_freq;
    file_aver.open("average.txt");
    file_freq.open("frequency.txt");
    sgenrand(RANDOMIZE);
    net = HyperbolicNet::read_hg("./20000.hg");
    net->buildNeighbors();
    int x, step;
    double fc, afc=0;  /* Frequency of C and last 5000 step average */
    file_aver << "T,S,theta,r,C" << endl;
    for (T = 1.2; T <= 1.2; T += 0.1)
    for (S = -0.2; S <= -0.2; S += 0.1)
    for (r = 0.05; r <= 1; r += 0.05)
    for (theta = 0.1; theta <= 2; theta += 0.1) {
        update_matrix(T, S);
        
#ifdef METRIC_CLUSTER
        init_by_metric_cluster();
#else
        init();
#endif
        for (step = 0; step < MC_STEPS; step++){
            for (x = 0; x < SIZE; x ++)
                update_stra((int)randi(SIZE));
            
            fc = stra_cnt[0]/(double)SIZE;
            if (step > MC_STEPS-REC_STEPS-1) afc += fc;
        	file_freq << step << ',' << fc << endl;
            if (step % REFRESH_FRE == 0)
            cout << "\rStep: " << step << "\tC: " << fc*100 << "              ";
            
        	if ((!stra_cnt[0]) || (!stra_cnt[1])){
                if (step++ < MC_STEPS-REC_STEPS) afc = stra_cnt[0] ? 1 : 0;
                break; 
            };
        }
        if (step > MC_STEPS-REC_STEPS)
            afc /= step + REC_STEPS - MC_STEPS;
        file_aver << T << ',' << S << ',' << theta << ',' << r << ',' << afc << endl;
        cout << "\rT: " << T << "\tS: " << S << "\ttheta: " << theta << "\tr: " << r 
             << "\t   avg_C: " << afc*100 << "              " << endl;
    }
    file_aver.close();
    file_freq.close();
    delete net;
    return 0;
}


