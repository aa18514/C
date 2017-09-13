/*
 * invalid_triangle.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef INVALID_TRIANGLE_HPP_
#define INVALID_TRIANGLE_HPP_
#include <stdexcept>
#include <string>
using namespace std;
class invalid_triangle_argument: public invalid_argument{
public:
	invalid_triangle_argument(const string& what):invalid_argument(what){}
};





#endif /* INVALID_TRIANGLE_HPP_ */
