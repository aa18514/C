#include "IE.h"
#include <Windows.h>
#include <iostream>
#include <String>
using namespace std; 

#define IE_URL_SIZE 5024
                      
string ie::get_location(HWND hwnd){
	char textBuffer[IE_URL_SIZE];
	HWND hwndEdit = FindWindowEx(hwnd, NULL, "EDIT", NULL);
  HWND handle = FindowEx(hwnd, NULL, "WorkerW", "Navigation Bar"); 
  handle = (NULL != handle) ? FindWindowEx(handle, NULL, "ReBarWindow32", NULL) : handle;
  handle = (NULL != handle) ? FindWindowEx(handle, NULL, "Adress Band Root", NULL) : handle;
  hwndEdit = FindWindowEx(handle, NULL, "Edit", NULL); 
  SendMessage(hwndEdit, WM_GETTEXT, (WPARAM)IE_URL_SIZE, (LPARAM)textBuffer)
  return '"' + string(textBuffer) + '"';
}

