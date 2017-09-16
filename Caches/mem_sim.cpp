/*
 * mem_sip.cpp
 *
 *  Created on: 4 Jan 2016
 *      Author: Asad Ahmad
 */
//implementation of single-level cache;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <stdint.h>
#include "mem_sim_initialize_mem.cpp"
#include "mem_sim_initialize_caches.cpp"
using namespace std;
void print(string &data, vector<uint16_t>& result);
void print_read_data(unsigned &block_index, string &read_write, unsigned &set_index, string &hit_miss, int &time, unsigned &word_bytes, unsigned &bytes, Caches &c1);
void set_cache (vector<uint16_t> &result, int &block_index, unsigned& word_index, unsigned &set_index, Caches &c1);
void maintain_list(Caches &c1, int &i, int &numOfentries, unsigned &set_index);
void print_write_data(unsigned& set_index, string &miss_hit, int &time);
int number_of_valid_entries (Caches &c1, unsigned &blocks_set, unsigned &set_index);
void get_from_mem(Caches & c1, Memory &M1, unsigned& set_index, int& block_index, int& word_index, unsigned &bytes, int &nbytes, unsigned block_addr);

int main(int argc, char* argv[]){
int numOfentries = 0;
int time = 0;
int result1;
unsigned bits = atoi(argv[1]);
unsigned bytes = atoi(argv[2]);
unsigned words_block = atoi(argv[3]);
unsigned blocks_set = atoi(argv[4]);
unsigned sets_cache = atoi(argv[5]);
int hit_time = atoi(argv[6]);
unsigned memory_read_time = atoi(argv[7]);
unsigned memory_write_time = atoi(argv[8]);
result1 = pow (2, bits)/(bytes*words_block); //number of block addresses
int blocks = blocks_set * sets_cache;
int nbytes = blocks*words_block*bytes;
int bytes_block =  words_block * bytes;
Caches c1(sets_cache, blocks_set, bytes, words_block); //data is a vector of words. Each word is a vector of bytes
Memory M1(result1, bytes_block); //Memory is a vector of blocks, each block is a vector of bytes.
//using cout as stdout;
//command line argument 1: Address Bits;
//command line argument 2: Bytes/Word;
//command line argument 3: Words/Block;
//command line argument 4: Blocks/Set;
//command line argument 5: Sets/Cache;
//command line argument 6: Hit Time;
//command line argument 7: Memory Read Time in Cycles/Block
//command line argument 8: Memory Write Time in Cycles/Block;
string miss_hit;
string line;
string command;
while(cin >> command){
	stringstream ss;
	if (command == "#"){
		string line;
		getline(cin, line);
	}
	if (command == "read-req"){
		string read_miss = "read-ack";
		unsigned addr;
		cin >> dec >> addr;
		unsigned word_addr = (addr/bytes);
		unsigned cache_size = (sets_cache)*(blocks_set); //cache_size in blocks;
		unsigned block_addr = (word_addr/words_block);
		unsigned set_index = block_addr % sets_cache;
		unsigned block_index = block_addr % cache_size;
		unsigned word_index = word_addr % (words_block);
		int bytes_block = bytes*words_block;
		ss << block_addr;
		bool not_found = true;
		if(sets_cache >= 1 && blocks_set > 1){
			for (int i = 0; i < blocks_set; i++){
				if(c1.s[set_index].b1[i].valid == false){
					c1.update_block(set_index, i, true, false, ss.str());
					numOfentries = number_of_valid_entries(c1, blocks_set, set_index);
					maintain_list(c1, i, numOfentries, set_index);
					time = memory_read_time + hit_time;
					for (int p = 0; p < bytes_block; p++){
						(c1.s[set_index].b1[i].data[p/bytes])[p % bytes] = M1.read_from_mem(block_addr, p);
					}
						block_index = i;
					    miss_hit = "miss";
					    i = blocks_set;
					    not_found = false;
				}
				else if ((c1.s[set_index].b1[i].valid == true) && (c1.s[set_index].b1[i].tag == ss.str())){
					block_index = i;
					int tem = c1.s[set_index].list[i];
					not_found = false;
					time = hit_time;
					maintain_list(c1, tem, i, set_index);
					miss_hit = "hit";
					i = blocks_set;
				}
			}
			if (not_found){
				miss_hit = "miss";
				time = memory_read_time + hit_time; 
				time = (c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].dirty) ? memory_write_time + time : time; 
				if(!c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].dirty == false){
					c1.update_block(set_index, temp, true, true, ss.str());
				}
				else{
					int addr1 = atoi((c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].tag).c_str());
					int set_addr = addr1 * sets_cache;
					//retrieving the block at the set and placing it in mem...
					for (int i = 0; i < bytes_block; i++){
						M1.data[block_addr][i] = (c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].data[i/bytes][i % bytes]);
					}
					//replacing the last block in that cache
					c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].tag = ss.str();
				}
				get_from_mem(c1, M1, set_index, c1.s[set_index].list[blocks_sets - 1], bytes_block, bytes, nbytes, block_addr);
				maintain_list(c1, c1.s[set_index].list[block_set - 1], block_sets - 1, set_index);
				block_index = c1.s[set_index].list[blocks_set - 1];
				//need to check for empty entries in the cache?
				//if there are no empty entries then replace the first entry in the cache with the appropiate value
			}
		}
		else if((blocks_set == 1) && (sets_cache >= 1) ){
			miss_hit = "miss";
			if(!c1.s[block_index].b1[0].valid){
				c1.s[block_index].b1[0].valid = true;
				c1.s[block_index].b1[0].dirty = false;
				c1.s[block_index].b1[0].tag = ss.str();
				for (int i = 0; i < bytes_block; i++){
					(c1.s[block_index].b1[0].data[i/bytes])[i % bytes] = M1.read_from_mem(block_addr, i);
				}
				time = memory_read_time + hit_time;
			}
			else{
				if(c1.s[block_index].b1[0].tag != ss.str()){
					time = (!c1.s[block_index].b1[block_addr % blocks_set].dirty) ? hit_time + memory_write_time : memory_read_time + memory_write_time + hit_time; 
					if(!c1.s[block_index].b1[block_addr % (blocks_set)].dirty){
						c1.update_block(block_index, block_addr % blocks_set, true, false, ss.str());
						for (int i = 0; i < bytes_block; i++){
							(c1.s[block_index].b1[0].data[i/bytes])[i % bytes] = M1.data[block_addr][i];
						}
					}
					else{
						for (int i = 0; i < bytes_block; i++){
							M1.data[atoi(c1.s[block_index].b1[0].tag.c_str())][i] = (c1.s[block_index].b1[0].data[i/bytes])[i % bytes];
						}
						c1.s[block_index].b1[0].tag = ss.str();
						for (int i = 0; i < bytes_block; i++){
							(c1.s[block_index].b1[0].data[i/bytes])[i % bytes] = M1.data[block_addr][i];
						}
						c1.s[block_index].b1[0].dirty = false;
					}
				}
			}
			 block_index= 0;
		}
		print_read_data(block_index, read_miss, set_index, miss_hit, time, word_index, bytes, c1);
	}

if(command == "write-req"){
	bool not_found = true;
	unsigned addr;
	cin >> dec >> addr;
	string data;
	cin >> data;
	vector<uint16_t> result;
	print(data, result);
	unsigned word_addr = addr/bytes;
	unsigned cache_size = (sets_cache)*(blocks_set);
	unsigned block_addr = (word_addr/words_block);
	unsigned set_addr = block_addr/blocks_set;
	unsigned set_index = set_addr % sets_cache;
	unsigned word_index = word_addr % words_block;
	ss << block_addr;
	not_found = true;
	if((sets_cache >= 1) && (blocks_set > 1)){
		for (int i = 0; i < blocks_set; i++){
			if(!c1.s[set_index].b1[i].valid){
				c1.update_block(set_index, i, true, true, ss.str());
				set_cache (result, i, word_index, set_index, c1);
				time = memory_read_time + hit_time;
				numOfentries = number_of_valid_entries(c1, blocks_set, set_index);
				maintain_list(c1, i, numOfentries - 1, set_index);
				miss_hit = "miss";
				i = blocks_set;
				not_found = false;
			}
			else if(c1.s[set_index].b1[i].valid && (c1.s[set_index].b1[i].tag == ss.str())){
				maintain_list(c1, i, c1.s[set_index].list[i], set_index);
				set_cache(result, i, word_index, set_index, c1);
				c1.s[set_index].b1[i].dirty = true;
				time = hit_time;
				miss_hit = "hit";
				i = blocks_set;
				not_found = false;
			}
		}

	if (not_found){
		time = 0; 
		if (words_block > 1){
				for (int l = 0; l < bytes_block; l++){
					(c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].data[l/bytes])[l % bytes] = M1.data[block_addr][l];
				}
				time += memory_read_time;
		}

		if(!c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].dirty){
			c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].dirty = true;
			c1.s[set_index].b1[c1.s[set_index].list[blocks_set - 1]].tag = ss.str();
			set_cache(result, block_sets - 1,word_index, set_index, c1);
			maintain_list(c1, c1.s[set_index].list[block_sets - 1], block_sets - 1, set_index);
		}
		
		else{
			for (int l = 0; l < bytes_block; l++){
				M1.data[atoi(c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].tag.c_str())][l] = (c1.s[set_index].b1[c1.s[set_addr].list[blocks_set - 1]].data[l/bytes])[l % bytes];
			}
			time += memory_write_time;
			c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].tag = ss.str();
			for (int l = 0; l < result.size(); l++){
				c1.s[set_index].b1[c1.s[set_index].list[blocks_set -1]].data[word_index][l] = result[l];
			}
			maintain_list(c1, c1.s[set_index].list[block_sets - 1], block_sets - 1, set_index);
		}
		time += hit_time; 
		miss_hit = "miss"; 
	}
}
	else if((sets_cache >= 1) && (blocks_set == 1)){
		miss_hit = "miss"; 
		if (!c1.s[set_index].b1[0].valid){
			c1.s[set_index].b1[0].valid = true;
			c1.s[set_index].b1[0].dirty = true;
			c1.s[set_index].b1[0].tag = ss.str();
			time = memory_write_time + hit_time;
			set_cache(result, 0, word_index, set_index, c1);
		}
		else{
			set_cache(result, 0, word_index, set_index, c1); 
			c1.s[set_index].b1[0].dirty = (c1.s[set_index].b1[0].tag == ss.str()) ? true : c1.s[set_index].b1[0].dirty; //if it is a hit we just replace the data in the block 
			time = (c1.s[set_index].b1[0].tag == ss.str()) ? hit_time : memory_write_time + hit_time; 
			c1.s[set_index].b1[0].tag = ss.str();
			if(c1.s[set_index].b1[0].tag != ss.str()){
			//bringing the address in from memory..
				if (c1.s[set_index].b1[0].dirty){
					time = (words_block == 1) ? time : memory_write_time + memory_read_time + hit_time; 
					for (int p = 0; p < bytes_block; p++){
						M1.data[atoi(c1.s[set_index].b1[0].tag.c_str())][p] = (c1.s[set_index].b1[0].data[p/bytes])[p % bytes];
					}
				}
				else
					c1.update_block(set_index, 0, true, true, ss.str()); 
			}
		}
	}
	print_write_data(set_index, miss_hit, time);
}

	else if (command == "flush-req"){
		int number_of_dirty_cycles = 0;
	//need to maintain consistency between cache and memory;
		for (int i = 0; i < sets_cache; i++){
			for (int j = 0; j < blocks_set; j++){
				if(c1.s[i].b1[j].valid && c1.s[i].b1[j].dirty){
					int set_addr = j * atoi((c1.s[i].b1[j].tag).c_str());
					for (int l = 0; l < nbytes; l++){
						M1.data[set_addr * blocks_set][l] = (c1.s[i].b1[j].data[l/bytes])[l % bytes];
					}
					c1.s[i].b1[j].dirty = false;
					number_of_dirty_cycles++;
				}
			}
		}
		int time = memory_write_time * number_of_dirty_cycles;
		cout << "flush-ack" << " " << time << endl;
	}


	else if(command == "debug-req"){
		cout << "debug-ack \n\n\n" << "Memory \n"; 
		int i, j; 
		for (i = 0; i < result1; i++){
			cout << dec << i << ": ";
			for (int j = 0; j < bytes_block; j++){
				cout << hex <<setfill('0') << right << setw(2) << (M1.data[i])[j];
			}
			cout << endl;
		}
		cout << "\n\n\n Cache \n";
		int num_entries = 0;
		for (i = 0; i < sets_cache; i++){
			for (j =0; j < blocks_set; j++){
				num_entries = (c1.s[i].b1[j].valid) ? num_entries + 1 : num_entries;
			}
		}
		for (i = 0; i < sets_cache; i++){
			cout << "S[" << i << "] ";
			for (j = 0; j < blocks_set ; j++){
				if(c1.s[i].b1[j].valid){
					string result = (c1.s[i].b1[j].dirty) ? "/d}" : "}";
					if(sets_cache >= 1 && blocks_set > 1)
						cout << "{" << "B" << c1.s[i].b1[c1.s[i].list[j]].tag << result << endl;
					else
						cout << "{" << "B" << c1.s[i].b1[j].tag << result << endl;
				}
			}
		}
		cout << "debug-ack-end" << endl;//checking the current state of the memory and the cache; //user defined debug output;
		}
	}
	return 0;
}

void print(string &data, vector<uint16_t>& result){
	for (unsigned int i = 0; i < data.size(); i = i+2){
		uint16_t temp = strtoul(data.substr(i, 2).c_str(), 0, 16);
		result.push_back(temp);
	}
}

void print_read_data(unsigned &block_index, string &read_write, unsigned &set_index, string& hit_miss, int &time, unsigned &word_bytes, unsigned &bytes, Caches &c1){
	cout << read_write << " " << set_index << " " << hit_miss << " " << time<< " ";
	for (int i = 0; i < bytes; i++){
		cout << hex << uppercase << setfill ('0') << right << setw(2) << c1.s[(set_index)].b1[block_index].data[i/bytes][i % bytes];
	}
	cout << endl;
}

void set_cache(vector<uint16_t> &result,int &block_index, unsigned& word_index, unsigned &set_index, Caches &c1){
	for (int l = 0; l < result.size(); l++){
		(c1.s[set_index].b1[block_index].data[word_index])[l] = result[l];
	}
}

void maintain_list(Caches &c1, int &i, int &numOfentries, unsigned &set_index){
	for (int j = numOfentries; j > 0; j--){
		c1.s[set_index].list[j] = c1.s[set_index].list[j-1];
	}
	c1.s[set_index].list[0] = i;
}

void print_write_data(unsigned& set_index, string &miss_hit, int &time){
	cout << "write-ack " << set_index << " " << miss_hit << " " << time << endl;
}

int number_of_valid_entries(Caches &c1, unsigned &blocks_set, unsigned &set_index){
	int numOfentries = 0;
	for (int j = 0; j < blocks_set; j++){
		if(c1.s[set_index].b1[j].valid)
			numOfentries++;
	}
	return numOfentries;
}

void get_from_mem(Caches & c1, Memory &M1, unsigned& set_index, int &block_index, int &word_index, unsigned &bytes, int &nbytes, unsigned block_addr){
	for (int l = 0; l < nbytes; l++){
		(c1.s[set_index].b1[c1.s[set_index].list[block_index]].data[l/bytes])[l % bytes] = M1.data[block_addr][l];
	}
}