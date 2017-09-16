#ifndef REGISTRY_H
#define	REGISTRY_H
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
using namespace std; 
string get_query(char* path, string filename);
string QueryKey(HKEY hKey, char* path, string filename);
#endif
