#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "hypernet.h"
#include "coordinate.h"
#include "netlib/random.h"
#include "netlib/common_net.h"

using namespace std;

#define RANDOMIZE   3145215
#define SIZE        5000
#define REFRESH_FRE 50
#define K           0.1
#define MC_STEPS    10000
#define REC_STEPS   5000
#define TRY_TIMES   10

//#define METRIC_CLUSTER

double gamma, beta, b;
HyperbolicNet *net;

typedef enum {
    STRA_C = 0,
    STRA_D = 1
} Strategy;

int stra_cnt[2];
int stra[SIZE];
double payoff_matrix[2][2] = {{1, 0},
                              {0, 0}};
#define update_matrix(b) do{\
    payoff_matrix[1][0]=b;\
    }while(0)


typedef struct SMetric{
    double sr;      /* Start r */
    double er;      /* End r */
    double st;      /* Start theta */
    double et;      /* End theta */
    Strategy stra;  /* Select strategy */
} Metric;

#ifdef METRIC_CLUSTER
void metric_cluster_stra(vector<Metric> &metric, Strategy default_stra){
    for (int i = 0; i < SIZE; i++)
        stra[i] = default_stra;
    HyperbolicPoint *points = net->getPoints();
    for (int j = 0; j < metric.size(); j++){
        for (int i = 0; i < net->totalVexNum(); i++){
            if (points[i].getR() > metric[j].er || points[i].getR() < metric[j].sr) continue;
            if ((metric[j].st > metric[j].et) && points[i].getTheta() > metric[j].st && points[i].getTheta() < metric[j].et || 
               ((metric[j].st > metric[j].et) && points[i].getTheta() < metric[j].st || points[i].getTheta() > metric[j].et)) continue;
            stra[i] = metric[j].stra;
        }
    }
    stra_cnt[0] = stra_cnt[1] = 0;
    for (int i = 0; i < SIZE; i++)
        stra_cnt[stra[i]]++;
}

void init_by_metric_cluster(){
    Metric m0 = {0, 99999, 0, M_PI, STRA_C};
    vector<Metric> metric;
    metric.push_back(m0);
    metric_cluster_stra(metric, STRA_D);
    //cout << stra_cnt[0] << ", " << stra_cnt[1] << endl;
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
    net = HyperbolicNet::read_hg("./5000.hg");
    net->buildNeighbors();
    int x, step;
    double fc, afc=0;  /* Frequency of C and last 5000 step average */
    for (b = 2.0; b < 2.5; b += 0.05){
        update_matrix(b);
        
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
        	file_freq << step << '\t' << fc << endl;
            if (step % REFRESH_FRE == 0)
            cout << "\rStep: " << step << "\tC: " << fc*100 << "              ";
            
        	if ((!stra_cnt[0]) || (!stra_cnt[1])){
                if (step++ < MC_STEPS-REC_STEPS) afc = stra_cnt[0] ? 1 : 0;
                break; 
            };
        }
        if (step > MC_STEPS-REC_STEPS)
            afc /= step + REC_STEPS - MC_STEPS;
        file_aver << b << '\t' << afc << endl;
        cout << "\rb: " << b << "\t   avg_C: " << afc*100 << "              " << endl;
    }
    file_aver.close();
    file_freq.close();
    delete net;
    return 0;
}


