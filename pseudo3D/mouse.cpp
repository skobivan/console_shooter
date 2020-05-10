#include "mouse.h"

bool Mouse::isLock = false;

Mouse::MouseButtonStates Mouse::leftButton = Mouse::NOTHING;

POINT Mouse::moving = POINT();
void Mouse::update() // Use this only once in cycle!!!!
{
    POINT currPos;
    GetCursorPos(&currPos);

    static POINT prevPos = currPos;

    moving.x = currPos.x - prevPos.x;
    moving.y = currPos.y - prevPos.y;

    if (isLock) SetCursorPos(2500, 540);

    GetCursorPos(&currPos);
    prevPos = currPos;

    if (isLeftButtonPressed()) {
        if (leftButton == NOTHING || leftButton == RELEASE) leftButton = CLICK;
        else leftButton = PRESS;
    } else {
        if (leftButton == CLICK || leftButton == PRESS) leftButton = RELEASE;
        else leftButton = NOTHING;
    }
}
