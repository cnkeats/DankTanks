#include "TileMap.h"

TileMap::~TileMap() {}

TileMap::TileMap() {
    // Initialize terrain array
    for (int y = 0; y < TERRAIN_SIZE_Y; ++y) {
        for (int x = 0; x < TERRAIN_SIZE_X; ++x) {
            if (TERRAIN_SIZE_Y - y < 5) {
                terrain[y][x] = 1;
            } else {
                terrain[y][x] = 0;
            }
        }
    }

    // Create tile for terrain
    terrain_tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    terrain_tile.setFillColor(sf::Color::Black);
    terrain_tile.setOutlineColor(sf::Color(127, 127, 127, 255));
    terrain_tile.setOutlineThickness(1);
}

void TileMap::Update(sf::RenderWindow &window) {
    for (int y = 0; y < TERRAIN_SIZE_Y; ++y) {
        for (int x = 0; x < TERRAIN_SIZE_X; ++x) {
            switch (terrain[y][x]) {
            case 0:
                continue;
                break;
            case 1:
                terrain_tile.setFillColor(sf::Color(63, 63, 63, 255)); // RGBA (red, green, blue, transparency)
                break;
            default:
                break;
            }
            terrain_tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(terrain_tile);
        }
    }
}
