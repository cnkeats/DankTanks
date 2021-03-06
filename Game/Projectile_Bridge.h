#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Bridge : public Projectile {
public:
    Projectile_Bridge(sf::Vector2f, sf::Vector2f);
    Projectile_Bridge(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Bridge(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Bridge() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:

};
