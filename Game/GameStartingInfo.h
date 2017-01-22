#pragma once
#include "Globals.h"

class GameStartingInfo {
public:
    GameStartingInfo();
    ~GameStartingInfo();
    void Reset();
    std::string toString();
    bool ClassesAreSelected();

    int p1_class_index;
    int p2_class_index;
    int p1_color_index;
    int p2_color_index;
    int map_index;
private:

};
