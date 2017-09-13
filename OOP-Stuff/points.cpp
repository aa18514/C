/*
 * points.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */
#include "points.hpp"
#include <cmath>
point::point(const double& ix, const double& iy): x(ix), y(iy){};
double point::get_dist(const point p1)const{
	double x_ = x -p1.x;
	double y_ = y - p1.y;
	return sqrt(x_*x_ + y_*y_);
}

double point::get_x() const{
	return x;
}
double point::get_y() const{
	return y;
}



