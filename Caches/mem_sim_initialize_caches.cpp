/*
 * mem_sim_initialize_caches.cpp
 *
 *  Created on: 22 Jan 2016
 *      Author: Asad Ahmad
 */
#include "mem_sim_initialize_caches.hpp"

Caches::Caches(unsigned &sets_cache, unsigned &blocks_set, unsigned bytes, unsigned &blocks){
	(*this).s.resize(sets_cache);
	for (int i = 0; i < sets_cache ; i++){
	((*this).s[i]).b1.resize(blocks_set);
	}

	int p = 0;
	while ( p < sets_cache ){
	for (int i = 0; i < blocks_set; i++){
	((*this).s[p]).b1[i].data.resize(blocks);
	}
	p++;
	}

	for (int q = 0; q < sets_cache; q++){
	for (int p = 0; p < blocks_set; p++){
	for (int u = 0; u < blocks; u++){
	((*this).s[q].b1[p].data[u]).resize(bytes);
	}
	}
	}
	for(int i = 0; i < sets_cache; i++){
	(*this).s[i].list = new int[blocks_set];
	}
	int i = 0;
	while (i < sets_cache){
	for(int j = 0; j < blocks_set ; j++){
	((*this).s[i]).b1[j].valid = false;
	}
	i++;
	}
}

void Caches:: update_block( int num, int block, bool valid, bool dirty, string addr){
	(*this).s[num].b1[block].tag = addr;
	(*this).s[num].b1[block].valid = valid;
	(*this).s[num].b1[block].dirty = dirty;
}

