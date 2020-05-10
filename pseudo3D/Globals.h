#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

using namespace std;

class Globals {
public:
    static wstring map;

    static int mapHeight;
    static int mapWidth;

    static int screenWidth;
    static int screenHeight;
    static float depth;

    static string nickname;
    static float FOV;
    static float mouseSensivity;

    static float elapsedTime;

    static string myIP;
    static string enemyIP;
};

#endif // GLOBALS_H
