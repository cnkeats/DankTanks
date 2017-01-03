#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <sstream>
#include <math.h>

extern sf::RenderWindow window;
extern sf::Font font;
extern sf::Text text_debug;
extern std::string debug_string;
extern std::string MENU_MAP_FILE;
extern std::string MENU_COLOR_FILE;
extern std::string TILE_FILE;
extern const int TILE_SIZE;
extern const int TILES_X;
extern const int TILES_Y;
extern const float PI;
extern const float PI_OVER_180;

std::string ToString(float);
std::string ToString(sf::Vector2i);
void DrawDebugString();
void CreateDebugString();

struct Tile {
    int status;
    sf::Vector2f velocity;
};
