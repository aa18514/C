#include "adobe.h"
#include <Windows.h>
#include <String>
using namespace std; 
#define ADOBE_PAGE_NUMBER 3

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