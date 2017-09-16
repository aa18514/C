#ifndef META_DATA_H
#define META_DATA_H 
#include <string> 
#include <chrono>
#include <windows.h> 
using namespace std; 
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
class meta_data{
public: 
		string value;
		meta_data(std::chrono::time_point<std::chrono::system_clock > Start, string date) : date_time(date), init(1), S(Start), key_down(true){} 
		string get_date_time();  
		void update_hold_delay(std::chrono::time_point<std::chrono::system_clock > End);
		float get_hold_delay();  
		void set_date_time(string date); 
		void update_clock(std::chrono::time_point<std::chrono::system_clock > start);
		bool get_key_down(); 
		void set_key_down(bool a);
private:
	string date_time;
	std::chrono::time_point<std::chrono::system_clock> S;
	float init; 
	float k; 
	bool key_down; 
};
#endif