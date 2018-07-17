/************************************************************
 *	Name: Pseudorandom Number Generator - Mersenne twister  *
 *	Copyright: GPL v3.0                                     *
 *	Author: Makoto Matsumoto & Takuji Nishimura             *
 *  Date: 1997                                              *
 *  Wiki: https://en.wikipedia.org/wiki/Mersenne_Twister    *
 ************************************************************/

#ifndef RANDOM_H
#define RANDOM_H

void sgenrand(unsigned long seed);
void lsgenrand(unsigned long seed_array[]);
double genrand();
double randf();
long randi(unsigned long LIM);

#endif
