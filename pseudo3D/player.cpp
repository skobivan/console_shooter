#include "player.h"

Player::Player(pair<float, float> startPos, float startAngle, float FOV) : GameObject(startPos, startAngle, FOV) {}

void Player::logic()
{
    moveControl();
    gun.logic();
}

void Player::show(wchar_t* screen)
{
    for (int x = 0; x < Globals::screenWidth; ++x) {
        // Вычисляем угол проецирования луча в пространство для каждого столбца
        float rayAngle = (angle - FOV/2) + (float(x)/float(Globals::screenWidth)) * FOV;

        float stepSize = 0.1f; // размер шага для луча, уменьшите для лучшего разрешения
        float distanceToWall = 0.0f;

        bool hitWall = false; // true, когда луч пересекает стену
        bool boundary = false; // true, когда луч пересекает границу между двумя стенами

        auto eye = pair<float, float>(sin(rayAngle), cos(rayAngle)); // Единичный вектор луча в пространстве игрока

        while(!hitWall && distanceToWall < Globals::depth) {
            distanceToWall += stepSize;
            auto test = pair<int, int>(int(position.first + eye.first * distanceToWall),
                                       int(position.second + eye.second * distanceToWall));

            // проверяем в пределах ли луч
            if (test.first < 0 || test.first >= Globals::mapWidth || test.second < 0 || test.second >= Globals::mapHeight) {
                hitWall = true;
                distanceToWall = Globals::depth;
            } else {
                // проверка на стену
                if (Globals::map.c_str()[test.first * Globals::mapWidth + test.second] == '#') {
                    // луч попал в стену
                    hitWall = true;

                    // затемнение стены в зависимости от расстояния
                    vector<pair<float, float>> p;

                    for (int tx = 0; tx < 2; ++tx) {
                        for (int ty = 0; ty < 2; ++ty) {
                            float vy = float(test.second) + ty - position.second;
                            float vx = float(test.first) + tx - position.first;
                            float d = sqrt(vx*vx + vy*vy);
                            float dot = eye.first*vx/d + eye.second*vy/d;
                            p.push_back(make_pair(d, dot));
                        }
                    }
                    // сортируем от наиболее близких к дальним
                    sort(p.begin(), p.end(),
                         [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first;});

                    float bound = 0.01;
                    for (int i = 0; i < 3; ++i) if (acos(p.at(i).second) < bound) boundary = true;


                }
            }
        }

        int ceiling = float(Globals::screenHeight/2.0f) - Globals::screenHeight/float(distanceToWall);
        int floor = Globals::screenHeight - ceiling;

        short shade;
        if (distanceToWall <= Globals::depth / 4.0f) shade = 0x2588; // Очень близко
        else if (distanceToWall < Globals::depth / 3.0f) shade = 0x2593;
        else if (distanceToWall < Globals::depth / 2.0f) shade = 0x2592;
        else if (distanceToWall < Globals::depth) shade = 0x2591;
        else shade = ' '; // Слишком далеко

        if (boundary) shade = ' ';

        for (int y = 0; y < Globals::screenHeight; ++y) {
            if (y <= ceiling)
                screen[y*Globals::screenWidth + x] = ' ';
            else if (y <= floor)
                screen[y*Globals::screenWidth + x] = shade;
            else {
                float b = 1.0f - (float(y) - Globals::screenHeight/2.0f) / (float(Globals::screenHeight / 2.0f));
                if (b < 0.25) shade = '#';
                else if (b < 0.5) shade = 'x';
                else if (b < 0.75) shade = '.';
                else if (b < 0.9) shade = '-';
                else shade = ' ';
                screen[y*Globals::screenWidth + x] = shade;
            }
        }
    }
    swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", position.first, position.second, angle, 1.0f/Globals::elapsedTime);
    gun.show(screen);
}


void Player::move(pair<float, float> step)
{
    position.first += step.first;
    position.second += step.second;
}

void Player::moveControl()
{
//    float xStep = sinf(fAngle) * fSpeed * Globals::fElapsedTime;
//    float yStep = cosf(fAngle) * fSpeed * Globals::fElapsedTime;

    pair<float, float> step(0.0, 0.0);

    // TODO: other keys

    float moveAngle = angle;
    bool flgX = false;
    bool flgY = false;

    if (GetAsyncKeyState((unsigned short)'W') & 0x8000) flgY = true;
    if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
        moveAngle += M_PI/2;
        flgX = true;
    }
    if ((GetAsyncKeyState((unsigned short)'A') & 0x8000) && !flgX) {
        moveAngle -= M_PI/2;
        flgX = true;
    }
    if ((GetAsyncKeyState((unsigned short)'S') & 0x8000) && !flgY) {
        moveAngle = (moveAngle > angle) ? moveAngle + M_PI : moveAngle - M_PI;
        flgY = true;
    }
    if (flgX && flgY) moveAngle = angle + (moveAngle - angle)/2;

    if (flgX || flgY) {
        step.first = sin(moveAngle) * speed * Globals::elapsedTime;
        step.second = cos(moveAngle) * speed * Globals::elapsedTime;
    }
    if (Globals::map.c_str()[int(position.first)*Globals::mapWidth+int(position.second+step.second)] == '#')
        step.second = 0.0;
    if (Globals::map.c_str()[int(position.first+step.first)*Globals::mapWidth+int(position.second)] == '#')
        step.first = 0.0;

    move(step);
//    static POINT prevCursorPos;
//    POINT cursorPos;
//    GetCursorPos(&cursorPos);
    float angleSpeed = Globals::mouseSensivity;
    angle += angleSpeed * Mouse::moving.x /*(cursorPos.x - prevCursorPos.x)*/ * Globals::elapsedTime;
//    SetCursorPos(2500, 540);
//    GetCursorPos(&cursorPos);
//    prevCursorPos = cursorPos;


//    if (GetAsyncKeyState((unsigned short)'C') & 0x8000)
//        angle -= (speed * 0.75f) * Globals::elapsedTime;
//    if (GetAsyncKeyState((unsigned short)'V') & 0x8000)
//        angle += (speed * 0.75f) * Globals::elapsedTime;
}
