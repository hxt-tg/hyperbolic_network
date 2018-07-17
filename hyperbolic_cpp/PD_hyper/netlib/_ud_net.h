/****************************
 *	Name: netlib            *
 *  Module: Undirected Net  * 
 *	Copyright: GPL v3.0     *
 *  Date: Aug. 2017         *
 *	Author: Xintao Hu       *
 ****************************/

#ifndef _UD_NET_H
#define _UD_NET_H

#include <iostream>
#include <string>
#include <vector>
#include "_basic_type.h"

/****************************
 *	Name: netlib            *
 *  Module: Undirected Net  * 
 *	Copyright: GPL v3.0     *
 *  Date: Aug. 2017         *
 *	Author: Xintao Hu       *
 ****************************/
 
/* Alias */
#define addEdge(v1, v2) addLink((v1), (v2))
#define removeEdge(v1, v2) removeLink((v1), (v2))
#define totalEdgesNum() totalLinksNum()
#define getNeighborsByEdges() getNeighborsByLinks()
#define edges_bidirected() links_bidirected()
#define edges_csv() links_csv()
#define edges_details() links_details()
#define edges_details_horizontal() links_details_horizontal()
#define isNeighbor(x, y) isLinked((x), (y))
#define total_edges() total_links()


typedef Vexid *NeighborArray;

typedef NeighborArray NeiArr;

class UndirectedNet{
	
	friend std::ostream& operator<<(std::ostream& out, const UndirectedNet& net){
		out << net.details() << std::endl;
    	return out;
	}
	
	public:
		explicit UndirectedNet(int vex_num = 0);
		~UndirectedNet();
		
	public:
		/* Operations */
		bool addLink(Vexid vex1, Vexid vex2);
		bool removeLink(Vexid vex1, Vexid vex2);
		bool buildNeighbors();
		
		/* Properties */
		inline int totalVexNum() const {
			return vn;
		}
		
		inline int totalLinksNum() const {
			return ln;
		}
		
		inline int totalDegree() const {
			return ln * 2;
		}
		
		inline int vexDegree(Vexid vex) const {
			if (vex < 0 || vex >= vn) return 0;
			return h[vex].ln + v[vex].ln;
		}
		
		inline double avgDegree() const {
			return ln*2.0/vn;
		}
		
		inline NeighborArray &getNeighbors(Vexid vex) const {
			if (nei) return nei[vex];
//			else return getNeighborsByLinks(vex);
		}
		
		NeighborArray getNeighborsByLinks(Vexid vex) const;
		
		std::string links_bidirected() const;
		std::string links_csv() const;
		std::string details() const;
		std::string links_details() const;
		std::string links_details_horizontal() const;
		bool isLinked(Vexid vex1, Vexid vex2) const;
		std::vector<Vexpair> total_links() const;
//		std::istream& operator>>(std::istream& in, const UndirectedNet& net);
		
	private:
		VexArr v;			/* Vertical Vertex */
		VexArr h;			/* Horizontal Vertex */
		int vn;				/* Vertex Num */
		int ln;				/* Link Num */
		NeighborArray *nei;	/* Neighbors */
};

typedef UndirectedNet UDNet;

#endif
