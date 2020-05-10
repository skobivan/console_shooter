#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>

#include "player.h"
#include "mouse.h"

enum GameMode {PLAY, PLAY_DEBUG};

class Engine
{
private:
    wchar_t* screen;
    HANDLE console;
    DWORD bytesWritten;
    GameMode gameMode;
//    Player * player;

    // вектор всех игровых объектов, у которых есть логика или отображение
    vector<GameObject*> gameObjects;
    void update();
    void render();
public:
    Engine(GameMode gameMode = PLAY);
    void run();
};

#endif // ENGINE_H
