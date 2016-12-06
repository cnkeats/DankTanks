#pragma once
#include "Globals.h"

struct Tile {
    int status;
    sf::Vector2f velocity;
};

class TileMap {
public:
    TileMap();
    ~TileMap();
    void Update(sf::RenderWindow &);
    void Generate();

    std::vector< std::vector<Tile> > tiles;

private:
    void PopulateTileTypes();
    void PopulateTiles();
    void PopulateVectorField();
    void DrawMap(sf::RenderWindow &);

    static const int TILE_SIZE = 15;
    static const int TILES_X = 128;
    static const int TILES_Y = 72;
    std::vector<sf::RectangleShape> tile_types;
    bool is_generated;
    enum LoadState {Generating, PopulatingVectorField, DrawingMap};
    LoadState load_state;
};
