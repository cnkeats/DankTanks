#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Globals.h"
#include "Application.h"

std::string debug_string = "";
sf::RenderWindow window;
sf::Font font;
const int TILE_SIZE = 10;
const int TILES_X = 192;
const int TILES_Y = 108;
const float PI_OVER_180 = 3.1415/180.0;

int main() {
    srand(time(NULL));

    Application app;

    return 0;
}
