#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_ImpactSplitBomb : public Projectile {
public:
    Projectile_ImpactSplitBomb(sf::Vector2f, sf::Vector2f);
    Projectile_ImpactSplitBomb(sf::Vector2f, sf::Vector2f, float, int);
    Projectile_ImpactSplitBomb(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile_ImpactSplitBomb() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, int);
private:

};
