#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Globals.h"
#include "Application.h"

sf::RenderWindow window;
sf::Font font;
sf::Text text_debug;
std::string debug_string = "";
const int TILE_SIZE = 15;
const int TILES_X = 128;     // 1920 / TILE_SIZE (5 = 384, 10 = 192, 15 = 128)
const int TILES_Y = 72 - 6; // 1080 / TILE_SIZE (5 = 216, 10 = 108, 15 = 72)
const float PI = 3.14159;
const float PI_OVER_180 = 3.14159 / 180.0;

int main() {
    CreateDebugString();

    srand(time(NULL));

    Application app;

    return 0;
}
