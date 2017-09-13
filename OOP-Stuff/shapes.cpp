/*
 * shapes.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */
#include "shapes.hpp"
ostream& operator<< (ostream& os, shapes& s1){
	os << s1.str();
	return os;
}



