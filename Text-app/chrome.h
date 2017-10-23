#ifndef CHROME_H 
#define CHROME_H
using namespace std;
#include "active_window_title.h" 
#include <string> 
#include <windows.h> 

class chrome : active_window_title{
	string get_location(HWND hwnd);	
}

#endif