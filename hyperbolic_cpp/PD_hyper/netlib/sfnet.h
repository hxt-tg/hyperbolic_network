/****************************
 *	Name: netlib            *
 *  Module: Scale-free Net  * 
 *	Copyright: GPL v3.0     *
 *  Date: Aug. 2017         *
 *	Author: Xintao Hu       *
 ****************************/

#ifndef SFNET_H
#define SFNET_H

#include "_ud_net.h"
#include "random.h"

class ScaleFreeNet : public UndirectedNet
{
	public:
		explicit ScaleFreeNet(int total_vex_num, int init_m0, bool silence_mode = true);
		
	public:
		bool addLink(Vexid vex1, Vexid vex2);
		bool fullConnectInitSFVex();
		bool fillSFVex_BAModel(int links_per_vex);
		bool fillSFVex_BAModel2(int links_per_vex);
		
	private:
		int curvex;			/* Current vertex */
		bool silence;
};

typedef ScaleFreeNet SFNet;

#endif
