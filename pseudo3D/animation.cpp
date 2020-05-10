#include "animation.h"

Animation::Animation(map<int, AnimationStruct<string>> stateToAnimation, string &texture, int &state)
{
    this->stateToAnimation = stateToAnimation;
    this->texture = &texture;
    this->state = &state;

}

void Animation::update()
{
    static int animationState = *state;
    static float delay = 0.0f;
    static int i = 0;

    int anPriority = stateToAnimation[animationState].priority;
    int currPriority = stateToAnimation[*state].priority;

    if (currPriority < anPriority || animationState == *state) {
        if (delay >= stateToAnimation[animationState].delay && i != stateToAnimation[animationState].animation.size()) {
            delay = 0.0f;
            *texture = stateToAnimation[animationState].animation[i++];
        }
        if (i == stateToAnimation[animationState].animation.size()) {
            delay = 0.0f;
            i = 0;
            animationState = *state;
        }
        delay += Globals::elapsedTime;
    } else {
        animationState = *state;
        delay = 0.0f;
        i = 0;
        *texture = stateToAnimation[animationState].animation[i];
    }
}
