#ifndef ANIMATIONOBJECT_H
#define ANIMATIONOBJECT_H

#include <string>
#include <map>

#include "animation_struct.h"
#include "Globals.h"

using namespace std;

class Animation
{
private:
    map<int, AnimationStruct<string>> stateToAnimation; // словарь для получения доступа к задержке и анимации через состояние
    int * state; // начальное состояние
    string * texture; // текстурка, на которую накладывается анимация
public:
    Animation(map<int, AnimationStruct<string>> stateToAnimation, string &texture, int &state);
    void update(); // обновление анимации
};

#endif // ANIMATIONOBJECT_H
