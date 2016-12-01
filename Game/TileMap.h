#pragma once
#include "Globals.h"

class TileMap {
public:
    TileMap();
    ~TileMap();
    void Update(sf::RenderWindow &);

    std::vector< std::vector<int> > tiles;
    std::vector< std::vector<sf::Vector2f> > vector_field;

private:
    void PopulateTiles();
    void PopulateVectorField();

    static const int TILE_SIZE = 10;
    static const int TILES_X = 160;
    static const int TILES_Y = 80;
    sf::RectangleShape tile;
};
