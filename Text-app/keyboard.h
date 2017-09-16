#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <windows.h>
class keyboard{
public:
	void send_ctrl_key();
	void send_c_key();
	void send_l_key();
	void release_c_key();
	void release_l_key();
	void release_ctrl_key(); 
	void send_ctrl_c(); 
	void send_ctrl_l_c();
	keyboard();
private: 
	INPUT ip;
};

#endif