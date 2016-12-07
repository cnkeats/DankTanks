#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"

class Player {
public:
    Player(sf::Vector2f);
    ~Player();
    void Update(TileMap* &);
    void InputFire(int);
    void InputRotate(int);
    void InputMove(TileMap* &, int);
    bool IsDead();

private:
    void UpdateProjectiles(TileMap* &);
    void UpdatePosition(TileMap* &);
    void SetTileCoords();
    bool IsInBounds(sf::Vector2i);
    sf::Vector2f GetDirectionVector();

    bool is_dead;
    int angle;
    float power;
    sf::Vector2i tile_coords;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
};
