#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <sstream>

extern std::string debug_string;
extern sf::RenderWindow window;
extern sf::Font font;
extern const int TILE_SIZE;
extern const int TILES_X;
extern const int TILES_Y;
extern const float PI_OVER_180;

std::string toString(int);
std::string toString(sf::Vector2i);
void debugString(std::string);
