/*
 * triangle.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */
#include "triangle.hpp"
#include "points.hpp"
#include "invalid_triangle.hpp"
#include <string>
#include <sstream>
using namespace std;
triangle::triangle(const point tp1, const point tp2, const point tp3):p1(tp1), p2(tp2), p3(tp3){
	if(p1.get_dist(p2) >= p2.get_dist(p3) + p3.get_dist(p1)){
		throw invalid_triangle_argument (string(" invalid triangle argument "));
	}
	else if(p2.get_dist(p3) >= p1.get_dist(p2) + p3.get_dist(p1)){
		throw invalid_triangle_argument (string(" invalid triangle argument "));
	}
	else if(p1.get_dist(p3) >= p2.get_dist(p3) + p1.get_dist(p2)){
		throw invalid_triangle_argument (string(" invalid triangle argument "));
	}
	}
double triangle::perimeter() const{
	return  p1.get_dist(p2) +
			p2.get_dist(p3) +
			p3.get_dist(p1);
}

string triangle::str() const{
	stringstream ss;
	ss << " TRIANGLE " << " PERIMETER: " << perimeter();
	return ss.str();
}
