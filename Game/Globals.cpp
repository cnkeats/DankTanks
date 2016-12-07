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
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setString(s);
    text.setColor(sf::Color::White);
    text.setPosition(0, 0);
    window.draw(text);
}
