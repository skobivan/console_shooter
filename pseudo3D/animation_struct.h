#ifndef ANIMATION_STRUCT_H
#define ANIMATION_STRUCT_H

#include <vector>

template <class T>
struct AnimationStruct { // структура для каждой анимации
    float delay;
    int priority; // приоритет прерывания другой анимации
    std::vector<T> animation; // кадры анимации
    AnimationStruct() {}
    AnimationStruct(int priority, float delay, std::vector<T> animation) {
        this->priority = priority;
        this->delay = delay;
        this->animation = animation;
    }
};

#endif // ANIMATION_STRUCT_H
