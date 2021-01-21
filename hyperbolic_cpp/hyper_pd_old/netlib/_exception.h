/*******************************
 *	Name: netlib               *
 *  Module: Exception Handler  * 
 *	Copyright: GPL v3.0        *
 *  Date: Aug. 2017            *
 *	Author: Xintao Hu          *
 *******************************/

#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>

class NetException : public std::exception{
	public:
		NetException(const char *info);
};

#endif
