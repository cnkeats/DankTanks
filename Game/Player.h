#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"

class Player {
public:
    Player(sf::Vector2f);
    ~Player();
    void Update(TileMap* &);
    void InputFire();
    void InputRotate(int);
    void InputMove(TileMap* &, int);
    bool IsDead();

private:
    void UpdateProjectiles(TileMap* &);
    void UpdateFallingPlayer(TileMap* &);
    void UpdateBarrel();
    void SetTileCoords();
    bool IsInBounds(sf::Vector2i);
    sf::Vector2f GetDirectionVector();

    bool is_dead;
    int projectile_type;
    int angle;
    float power;
    sf::Vector2i tile_coords;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
};
