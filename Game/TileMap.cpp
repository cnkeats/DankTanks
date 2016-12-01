#include "TileMap.h"

TileMap::~TileMap() {}

TileMap::TileMap() {
    PopulateTiles();

    for (int x = 90; x < 120; ++x) {
        for (int y = 10; y < 60; ++y) {
            tiles[x][y] = 1;
        }
    }

    PopulateVectorField();

    // Create tile default
    tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    tile.setFillColor(sf::Color::Black);
    tile.setOutlineColor(sf::Color(127, 127, 127, 255));
    tile.setOutlineThickness(1);
}

void TileMap::Update(sf::RenderWindow &window) {
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            switch (tiles[x][y]) {
            case 0:
                continue;
                break;
            case 1:
                tile.setFillColor(sf::Color(63, 63, 63, 255)); // RGBA (red, green, blue, transparency)
                break;
            case 2:
                tile.setFillColor(sf::Color::Cyan); // RGBA (red, green, blue, transparency)
                break;
            default:
                break;
            }
            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(tile);
        }
    }
}

void TileMap::PopulateTiles() {
    std::vector<int> column;

    for (int x = 0; x < TILES_X; ++x) {
        tiles.push_back(column);

        for (int y = 0; y < TILES_Y; ++y) {
            tiles[x].push_back(0);
        }
    }
}

void TileMap::PopulateVectorField() {
    std::vector<sf::Vector2f> column;

    for (int x = 0; x < TILES_X; ++x) {
        vector_field.push_back(column);

        for (int y = 0; y < TILES_Y; ++y) {
            if (tiles[x][y] != 0) {
                vector_field[x].push_back(sf::Vector2f(0.05f, -0.05f));
            } else {
                vector_field[x].push_back(sf::Vector2f(0.0f, 0.0f));
            }
        }
    }
}
