#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "render.h"

class GameObject: public Render
{
public:
    GameObject(pair<float, float> p, float a, float FOV);
    virtual void logic() {}
};

#endif // GAMEOBJECT_H
