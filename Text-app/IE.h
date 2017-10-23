#ifndef IE_H
#define	IE_H
#include <Windows.h>
#include <String>
#include "active_window_title.h"
using namespace std;
class ie:public active_window_title{
public: 
	ie(){}
	string get_location(HWND hwnd); 
}
#endif