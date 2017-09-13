/*
 * shapes.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef SHAPES_HPP_
#define SHAPES_HPP_
#include <iostream>
using namespace std;
class shapes{
public:
	virtual double perimeter() const=0;
	virtual ~shapes(){};
	virtual string str() const=0;
	friend ostream& operator<< (ostream& os, shapes& s1);
};



#endif /* SHAPES_HPP_ */
