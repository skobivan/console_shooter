#include "loader.h"

/*
 * Подгрузчик анимации.
 * На вход подается путь к конфиг файлу анимации, словарь, переводящий состояние в анимацию, который надо заполнить и название анимаций
 * Функция может вернуть ошибку при открытии файла или папки.
 * Если все прошло успешно, то она вернет SUCCES, но это не значит, что сами анимации были загружены корректно!!!
*/
Loader::ErrorStates Loader::loadAnimation(string path, map<int, AnimationStruct<string>> &stateToAnimation, vector<string> aNames)
{
    ifstream cfg(path);
    string aPath;
    string cmd;
    AnimationStates STATE = BEGIN;
    int currState = -1;
    if (!cfg.is_open()) return CANNOTOPENCFG;
    while (!cfg.eof()) {
        cfg >> cmd;
        if (STATE == ANIMATION_PATH) {
            aPath = cmd;
            STATE = ANIMATION_READY;
        }
        else if (STATE == ANIMATION_BUILD) {
            if (cmd == "PRIORY") STATE = PRIORY;
            if (cmd == "DELAY") STATE = DELAY;
            if (cmd == "DIR") STATE = DIRECTORY;
            if (cmd == "END") STATE = ANIMATION_READY;
        }
        else if (STATE == DELAY) {
            stateToAnimation[currState].delay = stof(cmd);
            STATE = ANIMATION_BUILD;
        }
        else if (STATE == PRIORY) {
            stateToAnimation[currState].priority = stoi(cmd);
            STATE = ANIMATION_BUILD;
        }
        else if (STATE == DIRECTORY) {
            stateToAnimation[currState].animation.clear();
            string dirPath = aPath + "/" + cmd;

            vector<string> fileNames;
            DIR *dir;
            struct dirent *ent;
            if (dir = opendir(dirPath.c_str())) {
                //              /* print all the files and directories within directory */
                while ((ent = readdir(dir)) != NULL) {
                    fileNames.push_back(string(ent->d_name));
                }
                closedir(dir);
            } else {
                //              /* could not open directory */
                return CANNOTOPENDIR;
            }

            fileNames.erase(fileNames.begin());
            fileNames.erase(fileNames.begin());

            for (auto name : fileNames) {
                string filePath = dirPath + '/' + name;
                ifstream fin(filePath);
                if (fin.is_open()) {
                    string buf;
                    getline(fin, buf, '\0');
                    fin.close();
                    buf.erase(remove(buf.begin(), buf.end(), '\n'), buf.end());
                    stateToAnimation[currState].animation.push_back(buf);
                } else {
                    return CANNOTOPENFILE;
                }
            }

            STATE = ANIMATION_BUILD;
        }
        if (cmd == "ANIMATIONS_PATH") STATE = ANIMATION_PATH;
        if (STATE == ANIMATION_READY) {
            for (int i = 0; i < aNames.size(); ++i) {
                if (cmd == aNames.at(i)+"_ANIMATION") {
                    stateToAnimation[i] = AnimationStruct<string>();
                    currState = i;
                    STATE = ANIMATION_BUILD;
                    break;
                }
            }
        }
        if (cmd == "FILE_END") break;
    }
    cfg.close();

    return SUCCES;
}

/*
 * Подгрузчик настроек.
 * На вход подается путь к файлу настроек.
 * Функция возвращает ошибку при открытии файла.
 * Однако если она вернула SUCCES, это еще не значит, что все загружено корректно!!!
 */
Loader::ErrorStates Loader::loadSettings(string path)
{
    ifstream settingsFile(path);
    string cmd;
    if (!settingsFile.is_open()) return CANNOTOPENCFG;
    while (!settingsFile.eof()) {
        settingsFile >> cmd;

        if (cmd == "my_ip") settingsFile >> Globals::myIP;
        else if (cmd == "enemy_ip") settingsFile >> Globals::enemyIP;
        else if (cmd == "nickname") settingsFile >> Globals::nickname;
        else if (cmd == "mouse_sensitivity") {
            string a;
            settingsFile >> a;
            Globals::mouseSensivity = stof(a);
        } else if (cmd == "FOV") {
            string a;
            settingsFile >> a;
            Globals::FOV = stof(a)/180*3.14f;
        } else if (cmd == "map_path") {
            string mapPath;
            settingsFile >> mapPath;
            ifstream mapFile(mapPath);

            if (!mapFile.is_open()) return CANNOTOPENFILE;

            string buf;
            getline(mapFile, buf, '\0');
            mapFile.close();
            buf.erase(remove(buf.begin(), buf.end(), '\n'), buf.end());
            Globals::map = wstring(buf.begin(), buf.end());
        } else if (cmd == "map_width") {
            settingsFile >> cmd;
            Globals::mapWidth = stoi(cmd);
        } else if (cmd == "map_height") {
            settingsFile >> cmd;
            Globals::mapHeight = stoi(cmd);
        } else if (cmd == "screen_width") {
            settingsFile >> cmd;
            Globals::screenWidth = stoi(cmd);
        } else if (cmd == "screen_height") {
            settingsFile >> cmd;
            Globals::screenHeight = stoi(cmd);
        } else if (cmd == "depth") {
            settingsFile >> cmd;
            Globals::depth = stof(cmd);
        }
        if (cmd == "FILE_END") break;
    }
    settingsFile.close();
    return SUCCES;
}
