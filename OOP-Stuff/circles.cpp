/*
 * circles.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */
#include "circles.hpp"
#include "points.hpp"
#include <string>
#include <sstream>
#include "invalid_radius.hpp"
circles::circles( point to,  double tradius): o(to), radius(tradius){
	if (radius <= 0){
		throw invalid_circle_argument (string("invalid radius"));
	}
}
double circles::perimeter()const {
	return (6.28*radius);
}

string circles::str() const{
	stringstream ss;
	ss << " CIRCLES " << " PERIMETER: " << perimeter();
	return ss.str();
}


