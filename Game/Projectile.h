#include "math.h"
#include "Globals.h"
#include "TileMap.h"

class Projectile {
public:
    Projectile();
    ~Projectile();
    void Update(sf::RenderWindow &, TileMap* &);

private:
    sf::RectangleShape sprite;
    sf::Vector2f velocity;
    sf::Vector2i grid_coords;
    static const int TILE_SIZE = 10;
    static const int TILES_X = 160;
    static const int TILES_Y = 80;
    bool isInBounds(sf::Vector2i);
};
