#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Cardinal : public Projectile {
public:
    Projectile_Cardinal(sf::Vector2f, sf::Vector2f);
    Projectile_Cardinal(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Cardinal(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Cardinal() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:

};
