#include "gun.h"

Gun::Gun() : GameObject(pair<float, float>(0, 0), 0, 0)
{

}

Gun::Gun(string cfgPath) : GameObject(pair<float, float>(0, 0), 0, 0)
{
    vector<string> aNames;
    aNames.push_back("STAND");
    aNames.push_back("MOVE");
    aNames.push_back("SHOOT");

    Loader::loadAnimation(cfgPath, stateToAnimation, aNames);
//    else while(1) cout << "NOOO";

    texture = stateToAnimation[STAND].animation[0];

    animation = new Animation(stateToAnimation, texture, state);
}

void Gun::show(wchar_t *screen)
{
    animation->update();
//    texture = animation->getTexture();
    for (int i = 0; i < Globals::screenHeight*Globals::screenWidth; ++i) {
        if (texture.at(i) != '$') screen[i] = texture.at(i);
    }
}

void Gun::logic()
{
    bool isMove = (GetAsyncKeyState('W') & 0x8000) ||
                     (GetAsyncKeyState('A') & 0x8000) ||
                     (GetAsyncKeyState('S') & 0x8000) ||
                     (GetAsyncKeyState('D') & 0x8000);
    state = STAND;
    if (isMove) state = MOVE;

    if (Mouse::leftButton == Mouse::CLICK) state = SHOOT;

}
