#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "netlib/random.h"
#include "netlib/sfnet.h"
#include "hyper.h"

using namespace std;


#define RANDOMIZE   3145215
#define SIZE        10000
#define INI_NODES   3
#define NEINUM      4
#define K           4
#define REFRESH_FRE 50
#define MC_STEPS    100000
#define REC_STEPS   5000
#define TRY_TIMES   10

double gamma, beta, b;
SFNet *net;

int stra_cnt[2];
int stra[SIZE];
double payoff_matrix[2][2] = {{1, 0},
                              {0, 0}};
#define update_matrix(b) do{\
    payoff_matrix[1][0]=b;\
    }while(0)

void init(){
    ;
}

double payoff(int x){
    return 0;
}

void update_stra(int x){
    ; 
}


int main(){
    
    sgenrand(time(NULL));
    char fname_net[80], fname_point[80];
    /* n_points, zeta, avg_degree, T, gamma */
    for (double T=0.3; T<0.701; T+=0.05){
        double avg_deg = 0;
        for (int j = 0; j < 30; j ++){
            HyperbolicRandomNet net(2000, 1, 6, 0.3, 3);
            avg_deg += net.avgDegree();
        }
        cout << T << ", " << avg_deg/30.0 << endl;
        
        /*
        sprintf(fname_net, "net.%g.csv", T);
        sprintf(fname_point, "points.%g.csv", T);
        ofstream fnet, fpoints;
        fnet.open(fname_net);
        fpoints.open(fname_point);
        fnet << net.links_csv() << endl;
        fpoints << net.pointsThetaRInfo() << endl;
        fnet.close();
        fpoints.close();
        */
    }
    
    
    return 0;
    ofstream file_aver, file_freq;
    file_aver.open("average.txt");
    file_freq.open("frequency.txt");
    
    sgenrand(RANDOMIZE);
    int x, step;
    double fc, afc=0;  /* Frequency of C and last 5000 step average */
    for (b = 1; b < 1.5; b += 0.01){
        update_matrix(b); 
        init();
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
        cout << "\rb: " << b << "\tavg_C: " << afc*100 << "              " << endl;
    }
    file_aver.close();
    file_freq.close();
    return 0;
}
