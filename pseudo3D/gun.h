#ifndef GUN_H
#define GUN_H

#include <fstream>
#include <deque>
//#include <string>
//#include <algorithm>

#include "gameobject.h"
#include "mouse.h"
#include "animation.h"
#include "loader.h"

using namespace std;

class Gun : public GameObject
{
public:
    enum State {STAND, MOVE, SHOOT};
private:
    string texture;
    int state = STAND;
    map<int, AnimationStruct<string>> stateToAnimation;
    Animation * animation;
public:
    Gun();
    Gun(string cfgPath);
    // Render interface
    void show(wchar_t *screen) override;
    // GameObject interface
    void logic() override;
};

#endif // GUN_H
