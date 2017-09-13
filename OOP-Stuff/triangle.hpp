/*
 * triangle.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_
#include "points.hpp"
#include "shapes.hpp"
#include <string>
#include <sstream>
class triangle: public shapes{
public:
	triangle(const point tp1, const point tp2, const point tp3);
	double perimeter() const;
	string str() const;
private:
	point p1;
	point p2;
	point p3;
};



#endif /* TRIANGLE_HPP_ */
