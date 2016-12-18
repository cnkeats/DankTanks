#include "Globals.h"

std::string toString(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

std::string toString(sf::Vector2i v) {
    return "(" + toString(v.x) + ", " + toString(v.y) + ")";
}

void debugString(std::string s) {
    debug_text.setString(s);
    window.draw(debug_text);
}
