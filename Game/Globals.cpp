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
void DrawDebugString() {
    text_debug.setString(debug_string);
    window.draw(text_debug);
}

void CreateDebugString() {
    text_debug.setFont(font);
    text_debug.setCharacterSize(20);
    text_debug.setColor(sf::Color::White);
    text_debug.setPosition(0, 0);
}
