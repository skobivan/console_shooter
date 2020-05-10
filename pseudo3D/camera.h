#ifndef CAMERA_H
#define CAMERA_H

#include <utility>

using namespace std;

struct Camera
{
    pair<float, float> position;
    float angle;
    float FOV;
    Camera(pair<float, float> position, float angle, float FOV) {this->position=position;this->angle=angle;this->FOV=FOV;}
};

#endif // CAMERA_H
