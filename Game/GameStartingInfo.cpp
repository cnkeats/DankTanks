#include "GameStartingInfo.h"

GameStartingInfo::~GameStartingInfo() {}

GameStartingInfo::GameStartingInfo() {
    Reset();
}

void GameStartingInfo::Reset() {
    p1_class_index = -1;
    p2_class_index = -1;
    p1_color_index = 4;
    p2_color_index = 0;
    map_index = -1;
}

bool GameStartingInfo::ClassesAreSelected() {
    return p1_class_index != -1 && p2_class_index != -1;
}

std::string GameStartingInfo::toString() {
    return "P1: (" + ToString(p1_class_index) + ", " + ToString(p1_color_index)
        + ") P2: (" + ToString(p2_class_index) + ", " + ToString(p2_color_index)
        + ") Map: (" + ToString(map_index) + ")";
}
