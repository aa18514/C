#include "meta_data.h"
#include <string> 
#include <chrono> 
#include <windows.h> 
#include <iostream> 
using namespace std; 


string meta_data::get_date_time(){
	return date_time; 
}


void meta_data::set_date_time(string a){
	date_time = a; 
}

bool meta_data::get_key_down(){
	return key_down; 
}

void meta_data::set_key_down(bool a){
	key_down = a; 
}

void meta_data::update_clock(std::chrono::time_point<std::chrono::system_clock > start){
	S = start; 
}

float meta_data::get_hold_delay(){
	return k; 
}

void meta_data::update_hold_delay(std::chrono::time_point<std::chrono::system_clock > End){
	k = (duration_cast<nanoseconds>(End - S).count())/1E9;
	cout << k << endl;
}
