#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"
#include "Projectile_AirSplitBomb.h"
#include "Projectile_BinaryTree.h"
#include "Projectile_Bridge.h"
#include "Projectile_ImpactSplitBomb.h"
#include "Projectile_Teleport.h"
#include "Projectile_Tunnel.h"

class Player {
public:
    Player(sf::Vector2f, int);
    ~Player();
    void Update(TileMap* &);
    void InputFire();
    void InputRotateClockwise();
    void InputRotateCounterClockwise();
    void InputPowerUp();
    void InputPowerDown();
    void InputMoveLeft(TileMap* &);
    void InputMoveRight(TileMap* &);
    void InputCycleProjectileType();
    void SetColor(sf::Vector2i);
    void UpdateInfo();
    bool IsTurnOver();
    bool IsDead();

private:
    void UpdateProjectiles(TileMap* &);
    void UpdateFallingPlayer(TileMap* &);
    void UpdateBarrel();
    void SetTileCoords();
    bool IsInBounds(sf::Vector2i);
    sf::Vector2f GetDirectionVector();

    bool is_real_time;
    bool fired;
    bool is_dead;
    int player_index;
    int hit_points;
    float power;
    int fuel;
    int angle;
    int budget;
    int selected_projectile;
    int selected_projectile_cost;
    std::string selected_projectile_string;
    sf::Vector2i tile_coords;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
    sf::RectangleShape sprite_barrel;
    sf::Text text_info_left;
    sf::Text text_info_right;
};
