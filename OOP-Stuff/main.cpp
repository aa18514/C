/*
 * main.cpp
 *
 *  Created on: 9 Dec 2015
 *      Author: aa18514
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "shapes.hpp"
#include "points.hpp"
#include "circles.hpp"
#include "triangle.hpp"
#include <stdexcept>
#include "invalid_radius.hpp"
#include "invalid_triangle.hpp"
using namespace std;

int main(){
	list<circles> l1;
	list<triangle> l2;
	vector<shapes*> s1;
	shapes* temp;
	list<circles>::iterator it;
	list<triangle>::iterator it2;
	ifstream infile;
	double x1;
	double y1;
	double x2, y2, x3, y3;
	double o;
	infile.open("circles.txt");
	try{
	while (infile >> x1 >> y1 >> o){
		l1.push_back(circles(point(x1, y1), o));
	}

	infile.close();
	infile.open("triangles.txt");
	while (infile >> x1 >> y1 >> x2 >> y2 >> x3 >> y3){
		l2.push_back(triangle(point(x1, y1), point(x2, y2), point (x3, y3)));
	}
	}
	catch(const invalid_circle_argument& e){
		infile.close();
		cout << e.what() << endl;
	}

	catch(const invalid_triangle_argument& e){
		infile.close();
		cout << e.what() << endl;
	}





	for (it = l1.begin(); it != l1.end(); ++it){
		s1.push_back(&(*it));
	}
	for(it2 = l2.begin(); it2 != l2.end(); ++it2){
		s1.push_back(&(*it2));
	}
	for (int i = 0; i < s1.size(); i++){
		cout << *(s1[i]) << endl;
	}


	return 0;
}


