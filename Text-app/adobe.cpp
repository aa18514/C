#include "adobe.h"
#include <Windows.h>
#include <String>
using namespace std; 
#define ADOBE_PAGE_NUMBER 3

string adobe::get_location(HWND hwnd){ 
	int pos = active_window_title.find_last_of(".")
	string filename = active_window_title.substr(1, pos - 1); 
	string path = get_query("SOFTWARE\\Adobe\\Acrobat Reader\\11.0\\AVGeneral\\CRecentFiles\\", filename); 
	return path; 
int pos = active_window_title.find_last_of(".");
                    string filename = active_window_title.substr(1, pos - 1);
                    string path = get_query( "SOFTWARE\\Adobe\\Acrobat Reader\\11.0\\AVGeneral\\CRecentFiles\\", filename);
                    text_file << ',' << path << endl;
                    cout << path << endl;
}

string get_adobe_page_number(HWND hwnd){
	char textBuffer[ADOBE_PAGE_NUMBER];
    HWND handle = FindWindowEx(hwnd, NULL, "AVL_AVView", "AVUICommandWidget");
    HWND hwndEdit;
    if(NULL != handle){
    	hwndEdit = FindWindowEx(handle, NULL, "Edit", NULL);
  		hwndEdit = FindWindowEx(handle, hwndEdit, "Edit", NULL);	
  }
  	SendMessage(hwndEdit, WM_GETTEXT, (WPARAM)ADOBE_PAGE_NUMBER, (LPARAM)textBuffer);	
  	return '"' + string(textBuffer) + '"';

}