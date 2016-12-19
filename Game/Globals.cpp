#include "Globals.h"

// Turns an int into a string
std::string toString(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

// Turns a vector of ints into an ordered pair string
std::string toString(sf::Vector2i v) {
    return "(" + toString(v.x) + ", " + toString(v.y) + ")";
}

// Draw debug_string to the screen
void debugString(std::string s) {
    debug_text.setString(s);
    window.draw(debug_text);
}
