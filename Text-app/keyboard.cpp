#include <windows.h>
#include "keyboard.h"
#include <iostream>
#include <time.h>
#define C 0x43;
#define L 0x4C;
using namespace std;

keyboard::keyboard(void){
    ip.type = INPUT_KEYBOARD;
}

void keyboard::send_ctrl_c(){
    send_ctrl_key(); 
    send_c_key(); 
    release_c_key(); 
    release_ctrl_key();
}

void keyboard::send_ctrl_l_c(){
       send_ctrl_key();
       send_l_key();
       send_c_key();
       release_c_key();
       release_l_key();
       release_ctrl_key();
}

void keyboard::send_ctrl_key(){
    ip.ki.wVk = VK_CONTROL; 
    ip.ki.dwFlags = 0;
    ip.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC); 
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(10); 
}

void keyboard::send_c_key(){
    ip.ki.wVk = C; 
    ip.ki.dwFlags = 0; 
    ip.ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC);
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(10);
}

void keyboard::release_c_key(){ 
	 ip.ki.wVk = C; 
     ip.ki.dwFlags = KEYEVENTF_KEYUP; /*indicates that the key is being released*/ 
     ip.ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC); 
     SendInput(1, &ip, sizeof(INPUT));  
     Sleep(50);
}

void keyboard::release_ctrl_key(){ 
	ip.ki.wVk = VK_CONTROL; 
    ip.ki.dwFlags = KEYEVENTF_KEYUP; 
    ip.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(50);
}

void keyboard::send_l_key(){
    ip.ki.wVk = L; 
    ip.ki.dwFlags = 0; 
    ip.ki.wScan = MapVirtualKey(0x4C, MAPVK_VK_TO_VSC);
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(50);
}

void keyboard::release_l_key(){
     ip.ki.wVk = L; 
     ip.ki.dwFlags = KEYEVENTF_KEYUP; /*indicates that the key is being released*/ 
     ip.ki.wScan = MapVirtualKey(0x4C, MAPVK_VK_TO_VSC); 
     SendInput(1, &ip, sizeof(INPUT));  
     Sleep(5);
}