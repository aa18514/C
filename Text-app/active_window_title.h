#ifndef ACTIVE_WINDOW_TITLE_H 
#define ACTIVE_WINDOW_TITLE_H
#include <string> 
#include <Windows.h> 
using namespace std; 

class active_window{
	public: 
		virtual void get_location()=0;
}


#endif