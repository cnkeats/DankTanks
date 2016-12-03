#include "math.h"
#include "Globals.h"
#include "TileMap.h"

class Projectile {
public:
    Projectile();
    ~Projectile();
    void Update(sf::RenderWindow &, TileMap* &);
    bool isExpired();

private:
    bool isInBounds();

    sf::RectangleShape sprite;
    sf::Vector2f velocity;
    sf::Vector2i tile_coords;
    static const int TILE_SIZE = 15;
    static const int TILES_X = 128;
    static const int TILES_Y = 72;
    bool is_expired;
};
