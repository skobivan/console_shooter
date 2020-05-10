#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>

//#include "Globals.h"



class Mouse
{
private:
    static bool isLock;
public:
    enum MouseButtonStates {NOTHING, CLICK, PRESS, RELEASE};
    static MouseButtonStates leftButton;
    static POINT moving;
    static bool isLeftButtonPressed() {return GetAsyncKeyState(VK_LBUTTON) & 0x8000;}
    static bool isRightButtonPressed() {return GetAsyncKeyState(VK_RBUTTON) & 0x8000;}
    static void update();
    static void lock() {isLock = true;}
    static void unlock() {isLock = false;}
};

#endif // MOUSE_H
