#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <fstream>
#include <map>
#include <string>
#include <dirent.h>
#include <algorithm>

#include "animation_struct.h"
#include "Globals.h"

using namespace std;

class Loader
{
private:
    enum AnimationStates {BEGIN, ANIMATION_PATH, ANIMATION_BUILD, ANIMATION_READY, PRIORY, DELAY, DIRECTORY};
public:
    enum ErrorStates {SUCCES, CANNOTOPENDIR, CANNOTOPENFILE, CANNOTOPENCFG};
    static ErrorStates loadAnimation(string path, map<int, AnimationStruct<string>> &stateToAnimation, vector<string> aNames);
    static ErrorStates loadSettings(string path);
};

#endif // TEXTURELOADER_H
