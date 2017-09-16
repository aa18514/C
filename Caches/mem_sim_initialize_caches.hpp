/*
 * mem_sim_initialize_caches.hpp
 *
 *  Created on: 21 Jan 2016
 *      Author: Asad Ahmad
 */

#ifndef MEM_SIM_INITIALIZE_CACHES_HPP_
#define MEM_SIM_INITIALIZE_CACHES_HPP_

#include <vector>
#include <string>
using namespace std;
class block{
public:
bool dirty;
bool valid;
string tag;
vector<vector<uint16_t> > data; //only read words and not seperate blocks
};

class Sets{
public:
vector<block> b1;
int *list;
};

class Caches{
public:
vector<Sets> s;
Caches(unsigned &sets_cache, unsigned &blocks_set, unsigned bytes, unsigned &blocks);
void update_block( int num, int block, bool valid, bool dirty, string addr);
};









#endif /* MEM_SIM_INITIALIZE_CACHES_HPP_ */
