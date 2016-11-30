#include "Globals.h"

class Projectile {
public:
    Projectile();
    ~Projectile();
    void Update(sf::RenderWindow &);

private:
    sf::RectangleShape sprite;
    sf::Vector2f velocity;
};
