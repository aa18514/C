/*
 * mem_sim_initialize_mem.hpp
 *
 *  Created on: 21 Jan 2016
 *      Author: Asad Ahmad
 */

#ifndef MEM_SIM_INITIALIZE_MEM_HPP_
#define MEM_SIM_INITIALIZE_MEM_HPP_
#include <vector>
#include <stdint.h>
using namespace std;
class Memory{
public:
	Memory(unsigned result1, int nbytes);
	uint16_t read_from_mem(unsigned& i, int& j);
	vector<vector<uint16_t> > data;
};


#endif /* MEM_SIM_INITIALIZE_MEM_HPP_ */
