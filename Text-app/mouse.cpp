#include "mouse.h"
#include <windows.h>
#define LEFT_BUTTON  (GetKeyState(VK_LBUTTON) & 0x100)
using namespace std; 
bool left_click()
{
    Sleep(2.5);
    if(LEFT_BUTTON != 0 )
        return true;
    else
        return false; 
}

