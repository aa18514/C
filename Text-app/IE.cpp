#include "IE.h"
#include <Windows.h>
#include <iostream>
#include <String>
using namespace std; 
#define IE_URL_SIZE 5024
                      
string get_ie_url(HWND hwnd){
	char textBuffer[IE_URL_SIZE];
	HWND hwndEdit = FindWindowEx(hwnd, NULL, "EDIT", NULL);
    HWND handle = FindWindowEx(hwnd, NULL, "WorkerW", "Navigation Bar");
    if (NULL != handle){
    	handle = FindWindowEx(handle, NULL, "ReBarWindow32", NULL);
        if (NULL != handle)
        	handle = FindWindowEx(handle, NULL, "Address Band Root", NULL);
    }
    hwndEdit = FindWindowEx(handle, NULL, "Edit", NULL);
  	SendMessage(hwndEdit, WM_GETTEXT, (WPARAM)IE_URL_SIZE, (LPARAM)textBuffer);	
  	return '"' + string(textBuffer) + '"';

}

