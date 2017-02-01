#include "Globals.h"
#include "TileMap.h"
#include "Explosion.h"
#include "Projectile.h"
#include "Projectile_AirSplitBomb.h"
#include "Projectile_BinaryTree.h"
#include "Projectile_Boomerang.h"
#include "Projectile_Bouncer.h"
#include "Projectile_Bridge.h"
#include "Projectile_Cardinal.h"
#include "Projectile_CrescentShield.h"
#include "Projectile_Digger.h"
#include "Projectile_ImpactSplitBomb.h"
#include "Projectile_Shotgun.h"
#include "Projectile_Teleport.h"
#include "Projectile_Tunnel.h"

struct ProjectileData {
    std::string name;
    int cost;
    Projectile *projectile;
};

class Player {
public:
    Player(unsigned int, bool, int, int, sf::Vector2f);
    ~Player();
    void Update(TileMap* &, std::vector<Player*> &);

    void Input(int);

    void SetPosition(sf::Vector2i);
    void SetActive();
    void SetOvertime();

    void UpdateHitPoints(int);
    void UpdateOvertime(bool);
    void AddBudget();

    bool IsTurnOver();
    bool IsDead();
    bool IsOnTile(sf::Vector2i);

private:
    void InputFire();
    void InputRotateClockwise();
    void InputRotateCounterClockwise();
    void InputPowerUp();
    void InputPowerDown();
    void InputMoveLeft(TileMap* &);
    void InputMoveRight(TileMap* &);
    void InputCycleProjectileType();
    void SetColor(int);
    bool IsInBounds(sf::Vector2i);
    sf::Vector2f GetDirectionVector();
    ProjectileData GetProjectileData(int, bool);

    bool is_turn_based;
    bool is_active;
    bool is_dead;
    bool is_overtime;
    bool has_fired;
    unsigned int player_index;
    int hit_points;
    float power;
    int fuel;
    int angle;
    int budget;
    int selected_projectile;
    int selected_projectile_cost;
    int shot_counter;
    int input_cooldown[8];
    bool input_status[8];
    std::string selected_projectile_string;
    sf::Vector2i tile_coords;
    std::vector<Explosion*> explosions;
    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
    sf::RectangleShape sprite_barrel;
    sf::Text text_info_left;
    sf::Text text_info_right;
};
