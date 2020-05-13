#ifndef PLAYER_H
#define PLAYER_H

//#include <string>
//#include <windows.h>
#include <cmath>
//#include <vector>
#include <algorithm>

//#include "gameobject.h"
//#include "Globals.h"
#include "gun.h"
#include "mouse.h"

using namespace std;

class Player : public GameObject
{
private:
    Gun * pistol;
    Gun * sniper;
    Gun * currGun;
    const float speed = 5.0f;
    void move(pair<float, float> step);
    void moveControl();
public:
    Player(pair<float, float> startPos, float startAngle, float FOV);
    enum PlayerStates {MOVE};
    void logic() override;
    void show(wchar_t* screen) override;

};

#endif // PLAYER_H
