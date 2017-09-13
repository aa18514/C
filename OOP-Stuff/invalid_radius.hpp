/*
 * invlaid_radius.hpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */

#ifndef INVALID_RADIUS_HPP_
#define INVALID_RADIUS_HPP_
#include <stdexcept>
#include <string>
using namespace std;
class invalid_circle_argument: public invalid_argument{
public:
	invalid_circle_argument(const string& what):invalid_argument(what){}
};




#endif /* INVLAID_RADIUS_HPP_ */
