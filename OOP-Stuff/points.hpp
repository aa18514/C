/*
 * points.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef POINTS_HPP_
#define POINTS_HPP_
class point{
public:
	point(const double& ix, const double& iy);
	double get_dist(const point p1) const;
	double get_x() const;
	double get_y() const;
private:
	double x, y;
};


#endif /* POINTS_HPP_ */
