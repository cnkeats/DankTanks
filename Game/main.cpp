#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Globals.h"
#include "Application.h"

sf::RenderWindow window;
sf::Font font;
sf::Text text_debug;
std::string debug_string = "";
std::string MENU_MAP_FILE = "menu_map.png";
std::string MENU_COLOR_FILE = "menu_color.png";
std::string TILE_FILE = "tile_10.png";
const int TILE_SIZE = 10;
const int TILES_X = 1920/10; // 1920 / TILE_SIZE (5 = 384, 10 = 192, 15 = 128)
const int TILES_Y = 1080/10; // 1080 / TILE_SIZE (5 = 216, 10 = 108, 15 = 72)
const float PI = 3.14159265;
const float PI_OVER_180 = 3.14159265/180.0;

int main() {
    CreateDebugString();

    srand(time(NULL));

    Application app;

    return 0;
}
