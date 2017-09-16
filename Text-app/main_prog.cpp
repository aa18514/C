#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "keyboard.h"
#include "mouse.h"
#include "IE.h"
#include "registry.h"
#include "adobe.h"
#define DIFFERENT_COORDINATES   !((p.x == new_p.x) && (p.y == new_p.y)
#define ACTIVE_WINDOW_TITLE_MAXSIZE 1000
#define MS_WORD active_window_title.find("Word") != string::npos
#define CHROME  active_window_title.find("Chrome") != string::npos
#define IE      active_window_title.find("Internet Explorer") != string::npos
#define ADOBE   active_window_title.find("Adobe") != string::npos
#define ACTIVE_WINDOW_TITLE MS_WORD||CHROME||IE||ADOBE
using namespace std;
string GetActiveWindowTitle(HWND &hwnd);
string get_clipboard_data();
string get_timestamp();

int main(){
    keyboard user_keyboard;
    ifstream text_filer2("text.csv");
    ofstream text_file;
    text_file.open("text.csv", ios::out| ios::app);
    string result, active_window_title, url;
    POINT p, new_p;
    HWND hwnd;
    string t; 
    if(text_filer2.peek() == std::ifstream::traits_type::eof())
        text_file << "date time , active window title , highlighted text , location" << endl;
    while(true){
            while(!left_click());
            GetCursorPos(&p);
            while(left_click());
            GetCursorPos(&new_p);
            /*already registered the left_click, so check to see if coordinates when the button was clicked and released are different*/
            if(DIFFERENT_COORDINATES)){ 
                    hwnd = GetForegroundWindow();
                    active_window_title = GetActiveWindowTitle(hwnd); 
                     if(ACTIVE_WINDOW_TITLE){
                        /*for more information refer to keyboard.cpp*/
                        Sleep(2);
                        user_keyboard.send_ctrl_c();
                    
                        if( OpenClipboard(NULL) && IsClipboardFormatAvailable(CF_TEXT)){ 
                            t = get_timestamp();
                            t.erase(t.length() - 1);
                            text_file << t + ',' + active_window_title + ',' + get_clipboard_data();      
                            CloseClipboard(); 
                        }    
                        if(IE){
                           text_file << ',' + get_ie_url(hwnd) << endl;
                        }
                        else if(CHROME){
                            user_keyboard.send_ctrl_l_c();
                            if(OpenClipboard(NULL) && IsClipboardFormatAvailable(CF_TEXT)){
                                url = get_clipboard_data();  
                                text_file <<',' +  url << endl;
                                CloseClipboard(); 
                            }
                        }
                        else if(ADOBE){
                            int pos = active_window_title.find_last_of(".");
                            string filename = active_window_title.substr(1, pos - 1);
                            string path = get_query( "SOFTWARE\\Adobe\\Acrobat Reader\\11.0\\AVGeneral\\CRecentFiles\\", filename);
                            text_file << ',' << path << endl;
                            cout << path << endl;
                        }
                        else if(MS_WORD){
                            /*
                            string path = get_query( "SOFTWARE\\Microsoft\\Office\\16.0\\Word\\Reading Locations\\", active_window_title);
                            text_file << ',' << path << endl;
                            cout << path << endl;
                            */
                        }
                        else{
                            text_file << endl; 
                        }
                    }
                }                    
            }
    return 0; 
    }

string get_timestamp(){
    time_t now = time(0);
    tm* localtm = localtime(&now); 
    return (asctime(localtm));
}
string GetActiveWindowTitle(HWND &hwnd)
{
    char wnd_title[ACTIVE_WINDOW_TITLE_MAXSIZE];
    GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
    return '"' + string(wnd_title) + '"';
}

string get_clipboard_data(){
    string rm; 
    HGLOBAL hglb = (GetClipboardData(CF_TEXT));
    LPSTR lpstr = LPSTR(GlobalLock(hglb));
    GlobalUnlock(hglb);     
    rm = string(lpstr); 
    rm.erase(remove(rm.begin(), rm.end(), '\r'), rm.end());
    rm.erase(remove(rm.begin(), rm.end(), '\n'), rm.end());
    rm.erase(remove(rm.begin(), rm.end(), '\x022'), rm.end());
    for(int i = 0; i < rm.size(); i++){
        if(rm[i] == '"'){
            rm.insert(i+1, string(1, '"')); 
            i = i + 2;       
        }
    } 
        return '"' + rm + '"';
}
