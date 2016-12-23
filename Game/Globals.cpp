#include "Globals.h"

// Turns an int into a string
std::string ToString(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

// Turns a vector of ints into an ordered pair string
std::string ToString(sf::Vector2i v) {
    return "(" + ToString(v.x) + ", " + ToString(v.y) + ")";
}

// Draw debug_string to the screen
void DrawDebugString(std::string s) {
    debug_text.setString(s);
    window.draw(debug_text);
}

void CreateDebugString() {
    debug_text.setFont(font);
    debug_text.setCharacterSize(20);
    debug_text.setColor(sf::Color::White);
    debug_text.setPosition(0, 0);
}
