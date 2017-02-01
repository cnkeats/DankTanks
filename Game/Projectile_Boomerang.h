#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Boomerang : public Projectile {
public:
    Projectile_Boomerang(sf::Vector2f, sf::Vector2f);
    Projectile_Boomerang(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Boomerang(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Boomerang() {};
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:
    sf::Vector2f original_velocity;
};
