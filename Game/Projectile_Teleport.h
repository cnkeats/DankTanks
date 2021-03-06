#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Teleport : public Projectile {
public:
    Projectile_Teleport(sf::Vector2f, sf::Vector2f);
    Projectile_Teleport(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Teleport(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Teleport() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:

};
