/*
 * mem_sim_initialize_mem.cpp
 *
 *  Created on: 21 Jan 2016
 *      Author: Asad Ahmad
 */
#include "mem_sim_initialize_mem.hpp"
#include <vector>
#include <stdint.h>
using namespace std;
Memory::Memory(unsigned result1, int nbytes){
	(*this).data.resize(result1);
	for (int i = 0; i < result1; i++){
	((*this).data[i]).resize(nbytes);
	}
	for (int i = 0; i < result1; i++){
	for (int j = 0; j < nbytes; j++){
		(*this).data[i][j] = 0;
	}
	}
}

uint16_t Memory::read_from_mem(unsigned& i, int& j){
	return (*this).data[i][j];
}



