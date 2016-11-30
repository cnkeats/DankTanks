#include "Globals.h"

class TileMap {
public:
    TileMap();
    ~TileMap();
    void Update(sf::RenderWindow &);

private:
    static const int TILE_SIZE = 20;
    static const int TERRAIN_SIZE_X = 80;
    static const int TERRAIN_SIZE_Y = 40;
    sf::RectangleShape terrain_tile;
    int terrain[TERRAIN_SIZE_Y][TERRAIN_SIZE_X];
};
