#ifndef ADOBE_H
#define	ADOBE_H
#include <Windows.h>
#include <string>
using namespace std;
class adobe{
public: 
	string get_location(HWND hwnd); 
}
string get_adobe_page_number(HWND hwnd);
#endif

