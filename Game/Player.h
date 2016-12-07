#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"

class Player {
public:
    Player(sf::Vector2f);
    ~Player();
    void Update(TileMap* &);
    void UpdateProjectiles(TileMap* &);
    void InputFire(int);
    void InputRotate(int);
    void InputMove(int);

private:
    sf::Vector2f GetDirectionVector();

    std::vector<Projectile*> projectiles;
    sf::RectangleShape sprite;
    int angle;
    float power;
};
