#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include "registry.h"
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
using namespace std;
string QueryKey(HKEY hKey, char* path, string filename){ 
    TCHAR    achKey[MAX_KEY_LENGTH];          // buffer for subkey name
    TCHAR    achClass[MAX_PATH] = TEXT("");   // buffer for class name 
    DWORD    cchClassName = MAX_PATH;         // size of class string 
    DWORD    cSubKeys=0;                      // number of subkeys 
    DWORD    cbName, cbMaxSubKey, cchMaxClass, cValues, cchMaxValue, cbMaxValueData, cbSecurityDescriptor;              
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode; 

    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 

    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
        char* buffer = new char[1024];
        DWORD lpData = 1024;
        LONG dwRes;
    if (cSubKeys)
        {
        for (i=0; i<cSubKeys; i++) 
            { 
            DWORD cValue = MAX_VALUE_NAME;
            TCHAR achValue2[MAX_VALUE_NAME];
            LONG dwRegOPenKey = RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey);
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime); 
             if (retCode == ERROR_SUCCESS) 
                {
                char temp[2000];
                DWORD lp = 2000;
                LONG dwRegOPenKey = RegOpenKeyEx(HKEY_CURRENT_USER, string(string(path) + string(achKey)).c_str(), 0, KEY_READ, &hKey);
                achValue2[0] = '\0';
                dwRes = RegEnumValue(hKey, 1, achValue2, &cValue, NULL, NULL, NULL, NULL);
                buffer[0] = '\0';
                dwRes = RegQueryValueEx(hKey, achValue2, 0, NULL, (LPBYTE)temp, &lp);
                string val = string(temp);
                int pos = val.find_last_of('/'); 
                string subs = val.substr(pos + 1, val.length() - 1);
                pos = subs.find_last_of(".");
                string r = subs.substr(0, pos);     
                if(active_window_title == r)
                    return val;
                }
            }
        } 
    delete [] buffer;
    return "path not found";
    }


string get_query(char* path, string filename)
{
HKEY hKey;
LONG dwRegOPenKey = RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey);
if(dwRegOPenKey == ERROR_SUCCESS)
    return QueryKey(hKey, path, active_window_title);
RegCloseKey(hKey);
}
