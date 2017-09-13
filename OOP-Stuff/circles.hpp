/*
 * circles.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef CIRCLES_HPP_
#define CIRCLES_HPP_
#include "points.hpp"
#include "shapes.hpp"
class circles:public shapes{
public:
	circles( const point to,  const double tradius);
	double perimeter() const;
	string str() const;
private:
	point o;
	double radius;
};




#endif /* CIRCLES_HPP_ */
