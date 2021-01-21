/****************************
 *	Name: netlib            *
 *  Module: Common Net Lib  * 
 *	Copyright: GPL v3.0     *
 *  Date: Aug. 2017         *
 *	Author: Xintao Hu       *
 ****************************/

#ifndef COMMON_NET_H
#define COMMON_NET_H

#include "_ud_net.h"

/* 
 * Net:		Full connected net, also named well-mix net.
 * Param:	[vex_num]	Total vertex number in the net.
 */
class FullConnectedNet : public UndirectedNet
{
	public:
		explicit FullConnectedNet(int vex_num, bool silence_mode = true);
	
	private:
		bool silence;
};
typedef FullConnectedNet WellMixNet, WMNet, FCNet;


/* 
 * Net:		Regular net, commonly graphed as a circle.
 * Param:	[vex_num]		Total vertex number in the net.
 * 			[links_num]		Links number for every vertex forward to following vertexes.
 *							For tranditional regular net, [links_num] is 2.
 */
class RegularNet : public UndirectedNet
{
	public:
		explicit RegularNet(int vex_num, int links_num, bool silence_mode = true);
	
	private:
		int links_num;
		bool silence;
};
typedef RegularNet RENet;


/* 
 * Net:		Fixed degree net, vertexes links randomly.
 * Param:	[vex_num]		Total vertex number in the net.
 * 			[avg_degree]	Average degree for this net. It will add links randomly until
 *							net average degree reaches this value.
 */
class FixedDegreeNet : public UndirectedNet
{
	public:
		explicit FixedDegreeNet(int vex_num, double avg_degree, bool silence_mode = true);
		
	private:
		double avg_degree;
		bool silence;
};
typedef FixedDegreeNet FDNet;


/* 
 * Net:		E-R random net, NOTICE it contains 2 kinds of algorithm.
 * Param:	[vex_num]		Total vertex number in the net.
 * 			[avg_degree]	Average degree for this net. It will add links randomly until
 *							net average degree reaches this value.
 */
class ERRandomNet : public UndirectedNet
{
	public:
		explicit ERRandomNet(int vex_num, int avg_degree, bool silence_mode = true);
		explicit ERRandomNet(int vex_num, double avg_degree, bool silence_mode = true);
		
	private:
		double avg_degree;
		bool silence;
};
typedef ERRandomNet ERNet;


/* 
 * Net:		Grid net.
 * Param:	[width]		Width of grid.
 * 			[height]	Height of grid.
 * 			[nei_num]	Number of neighbors of each vertex. Must be able to divided by 4.
 * Notice:	Number of vertices is [width] times [height].
 */
class GridNet : public UndirectedNet
{
	public:
		GridNet(int height, int width, int nei_num = 4, bool silence_mode = true);
		
	private:
		int height;
		int width;
		int nei_num;
		bool silence;
};
typedef GridNet Grid;


/* 
 * Net:		Cubic net.
 * Param:	[width]		Width of grid.
 * 			[height]	Height of grid.
 * 			[nei_num]	Number of neighbors of each vertex. Must be able to divided by 4.
 * Notice:	Number of vertices is [width] times [height].
 */
class CubicNet : public UndirectedNet
{
	public:
		CubicNet(int length, int width, int height, bool silence_mode = true);
		
	private:
		int length;
		int width;
		int height;
		bool silence;
};
typedef CubicNet Cube, CBNet;


/* 
 * Net:		Honeycomb net.
 * Param:	[honeycomb_width]	Width of honeycomb.
 * 			[honeycomb_height]	Height of honeycomb.
 * Methods: [combDetails()]		Returns info string of every honeycomb. For debugging.
 * Notice:	To define a honeycomb, you may specify the height and width of honeycomb.
 *          The hexagons' number of this net is [honeycomb_width] times
 *          [honeycomb_height]. Each hexagon has 6 vertices. Every vertex belongs to 
 *          3 hexagons. Therefore every 2 vertices can specify one hexagon. And the 
 *          number of vertices is 2*w*h. The number of links is 3*w*h. For example, 
 *          if you want to build a honeycomb net with 40000 vertices, you may create
 *          this net as HoneycombNet(200, 100) or HoneycombNet(100, 200). The boundary
 *          will be wrapped automatically. More details are in user handbook. 
 */
class HoneycombNet : public UndirectedNet
{
	public:
		explicit HoneycombNet(int honeycomb_width, int honeycomb_height, bool silence_mode = true);
		std::string combDetails() const;
		
	private:
		int hc_w;
		int hc_h;
		bool silence;
};
typedef HoneycombNet HCNet;


/* 
 * Net:		Kagome net.
 * Param:	[kagome_width]		Width of kagome structure.
 * 			[kagome_height]		Height of kagome structure.
 * Methods: [kagomeDetails()]	Returns info string of every kagome structure.
 * Notice:	See honeycomb net.
 */
class KagomeNet : public UndirectedNet
{
	public:
		explicit KagomeNet(int kagome_width, int kagome_height, bool silence_mode = true);
		std::string kagomeDetails() const;
		
	private:
		int kg_w;
		int kg_h;
		bool silence;
};
typedef KagomeNet KGNet;

#endif
