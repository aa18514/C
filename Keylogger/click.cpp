#include <iostream> 
#include <windows.h>
#include <sstream> 
#include <tchar.h>
#include <iomanip>
#include <map> 
#include <fstream>
#include <ctime> 
#include "omp.h"
#include <chrono>
#include <vector> 
#include <thread>
#include <cstdlib>
#include "simulate_keystrokes.h"
#include "meta_data.h"
#include <cstdlib>
#include <stdint.h>
#include <string> 

using namespace std;

using chrono::nanoseconds;
using chrono::duration_cast;

/*function prototypes */
string get_date_time(chrono::time_point<chrono::system_clock> Start);
void send_keys(); 
DWORD WINAPI init_data(LPVOID lpParam); 
DWORD WINAPI run_sim(LPVOID lpParam);

ofstream file_to_record; 
bool first_hit = true; 
bool spin_true = true;  
map<bool, int> key_press; 
INPUT input;
map<int, meta_data*> keystrokes;
map<int, string> keystroke_to_alphabet; 
map<string, meta_data*> keystrokes_saved;
KBDLLHOOKSTRUCT prev_hooked_key, hooked_key;
chrono::time_point<chrono::system_clock > Start, End;
int vPrev = 1; 
vector<int> keystroked; 
HHOOK hKeyboardHook;


void send_keys(void){
    input.ki.dwFlags = key_press[spin_true];
    SendInput(1, &input, sizeof(INPUT)); 
    spin_true = !spin_true; 
}

DWORD WINAPI run_sim(LPVOID lpParam){
	while(true){
		int nanoseconds_sleep_time = 2E8; 
		Sleep_For(nanoseconds_sleep_time, send_keys); 
	}
}

DWORD WINAPI init_data(LPVOID lpParam){
	for(int i = 0; i < 1000; i++)
	{
		stringstream ss; 
		ss << i; 
		keystroke_to_alphabet[i] = ss.str(); 
	}
	keystroke_to_alphabet[65] = "a"; 
	keystroke_to_alphabet[66] = "b"; 
	keystroke_to_alphabet[67] = "c"; 
	keystroke_to_alphabet[68] = "d"; 
	keystroke_to_alphabet[69] = "e"; 
	keystroke_to_alphabet[70] = "f"; 
	keystroke_to_alphabet[71] = "g"; 
	keystroke_to_alphabet[72] = "h"; 
	keystroke_to_alphabet[73] = "i"; 
	keystroke_to_alphabet[74] = "j"; 
	keystroke_to_alphabet[75] = "k"; 
	keystroke_to_alphabet[76] = "l"; 
	keystroke_to_alphabet[77] = "m"; 
	keystroke_to_alphabet[78] = "n"; 
	keystroke_to_alphabet[79] = "o"; 
	keystroke_to_alphabet[80] = "p"; 
	keystroke_to_alphabet[81] = "q"; 
	keystroke_to_alphabet[82] = "r"; 
	keystroke_to_alphabet[83] = "s"; 
	keystroke_to_alphabet[84] = "t"; 
	keystroke_to_alphabet[85] = "u"; 
	keystroke_to_alphabet[86] = "v"; 
	keystroke_to_alphabet[87] = "w"; 
	keystroke_to_alphabet[88] = "x"; 
	keystroke_to_alphabet[89] = "y";
	keystroke_to_alphabet[0x08] = "BACKSPACE"; 
	keystroke_to_alphabet[90] = "z";
	keystroke_to_alphabet[0x20] = "SPACE"; 
	keystroke_to_alphabet[0x09] = "TAB";
	keystroke_to_alphabet[0x2E] = "DEL";
}


LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam){
	int i;
	hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
	switch(wParam)
	{
		case WM_KEYDOWN:
					Start = chrono::high_resolution_clock::now();
					if(keystrokes.find(hooked_key.vkCode) == keystrokes.end())
					{
						keystrokes[hooked_key.vkCode] = new meta_data(Start, get_date_time(Start));
						keystroked.push_back(hooked_key.vkCode);
					}
					else if(keystrokes[hooked_key.vkCode] -> get_key_down())
					{
						keystrokes[hooked_key.vkCode] -> update_clock(Start); 
						keystrokes[hooked_key.vkCode] -> set_date_time(get_date_time(Start));	
						keystrokes[hooked_key.vkCode] -> set_key_down(false);
						keystroked.push_back(hooked_key.vkCode);	
					}
		break; 

		case WM_KEYUP: 
				End = chrono::high_resolution_clock::now();
				if(first_hit)
					first_hit = false;
				else
					file_to_record << keystroke_to_alphabet[vPrev].c_str() << "," <<  keystrokes[vPrev] -> get_date_time().c_str() << "," << keystrokes[vPrev] -> get_hold_delay()  << endl;
				keystrokes[hooked_key.vkCode] -> update_hold_delay(End); 
				if(!keystrokes[hooked_key.vkCode] -> get_key_down())
					keystrokes[hooked_key.vkCode] -> set_key_down(true);
				for(i = 0; i < keystroked.size(); i++)
				{
					if(keystroked[i] == hooked_key.vkCode)
					{
						vPrev = keystroked[i]; 
						keystroked.erase(keystroked.begin() +  i);
						break;
					}
				}
		break; 
			
	} 
	return CallNextHookEx(hKeyboardHook, code, wParam, lParam);
}

int main(){ 
    file_to_record.open("data.csv",fstream::out | std::fstream::app );
	spin_true = true; 
    key_press[true] = 0; 
    key_press[false] = KEYEVENTF_KEYUP;
    input.type = INPUT_KEYBOARD; 
    input.ki.wScan = 0; 
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = 65 /*symbol for a*/;
	DWORD DwordThreadID[2];
	HANDLE hThreadIdArray[2] = {
									CreateThread(NULL, 0, init_data, NULL, 0, &DwordThreadID[0]), 
									CreateThread(NULL, 0, run_sim, NULL, 0, &DwordThreadID[1])
							   }; 
	HHOOK hInstance = SetWindowsHookEx(WH_KEYBOARD_LL, hook_proc, 0, 0);
	MSG msg; 
	while(!GetMessage(&msg, NULL, NULL, NULL)){
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	UnhookWindowsHookEx(hInstance);
	return 0;
}

string get_date_time(std::chrono::time_point<std::chrono::system_clock> Start){
 	SYSTEMTIME st;
 	GetLocalTime(&st); 
 	char buffer[ 256 ];
    sprintf( buffer, "%d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return buffer;
}
