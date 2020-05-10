#include "engine.h"

Engine::Engine(GameMode gameMode)
{

    Loader::loadSettings("./resources/settings.txt");

    this->gameMode = gameMode;
    screen = new wchar_t[Globals::screenWidth*Globals::screenHeight];
    console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    bytesWritten = 0;
    gameObjects.push_back(new Player(pair<float, float>(10, 10), 0, Globals::FOV)); // первым всегда должен быть игрок

    Mouse::lock();
}

void Engine::run() {
    auto t0 = chrono::system_clock::now();
    while(!(GetAsyncKeyState((unsigned short)'Q') & 0x8000)) {
        auto t1 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = t1 - t0;
        t0 = t1;
        Globals::elapsedTime = elapsedTime.count();
        Mouse::update();
        update();
        render();
    }
}

void Engine::update()
{
    for (auto it : gameObjects) it->logic();
}

void Engine::render() {
    for (auto it : gameObjects) it->show(screen);

    // отображение объектов в консоли
    // Display Frame
    screen[Globals::screenWidth * Globals::screenHeight - 1] = '\0';
    WriteConsoleOutputCharacter(console, screen, Globals::screenWidth * Globals::screenHeight, { 0,0 }, &bytesWritten);
}
