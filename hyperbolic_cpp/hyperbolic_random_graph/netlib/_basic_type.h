/*************************
 *	Name: netlib         *
 *  Module: Basic Types  * 
 *	Copyright: GPL v3.0  *
 *  Date: Aug. 2017      *
 *	Author: Xintao Hu    *
 *************************/

#ifndef BASIC_TYPE_H
#define BASIC_TYPE_H

#include "_exception.h"

typedef int Vexid;
typedef Vexid Vexpair[2];

/* Structures */
typedef struct LNode{
	Vexid v1;			/* Vertex 1 */
	Vexid v2;			/* Vertex 2 */
	struct LNode *nv;	/* Next vertical node */
	struct LNode *nh;	/* Next horizontal node */
} *Link;

typedef struct{
	int ln;				/* Link Num */
	Link next;			/* Point to next Node */
} Vex, *VexArr;

#endif
