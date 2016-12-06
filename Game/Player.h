#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"

class Player {
public:
    Player();
    ~Player();
    void Update(sf::RenderWindow &, TileMap* &);
    void UpdateProjectiles(sf::RenderWindow &, TileMap* &);
    void InputFire(int);
    void InputRotate(int);
    void InputMove(int);

private:
    sf::Vector2f GetDirectionVector();

    static const int TILE_SIZE = 15;
    static const int TILES_X = 128;
    static const int TILES_Y = 72;
    static const float PI_OVER_180 = 3.1415/180.0;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
    int angle;
    float power;
};
