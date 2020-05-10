#ifndef RENDER_H
#define RENDER_H

#include "camera.h"


using namespace std;

class Render: public Camera
{
public:
    Render(pair<float, float> p, float a, float FOV);
//    Render() : Camera(make_pair(0.0f, 0.0f), 0, 0) {}
    virtual void show(wchar_t* screen) {}
};

#endif // RENDER_H
