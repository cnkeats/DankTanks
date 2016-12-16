#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"
#include "Projectile_Bomb.h"
#include "Projectile_ImpactSplitBomb.h"
#include "Projectile_Tile.h"
#include "Projectile_Teleport.h"

class Player {
public:
    Player(sf::Vector2f, sf::Color);
    ~Player();
    void Update(TileMap* &);
    void InputFire();
    void InputRotateClockwise();
    void InputRotateCounterClockwise();
    void InputMoveLeft(TileMap* &);
    void InputMoveRight(TileMap* &);
    void InputSetProjectileType(int i);
    bool IsDead();

private:
    void UpdateInput(TileMap* &);
    void UpdateProjectiles(TileMap* &);
    void UpdateFallingPlayer(TileMap* &);
    void UpdateBarrel();
    void SetTileCoords();
    bool IsInBounds(sf::Vector2i);
    sf::Vector2f GetDirectionVector();

    bool is_dead;
    bool input_fire;
    bool input_rotate_clockwise;
    bool input_rotate_counter_clockwise;
    bool input_move_left;
    bool input_move_right;
    int projectile_type;
    int angle;
    float power;
    sf::Vector2i tile_coords;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
    sf::RectangleShape sprite_barrel;
};
