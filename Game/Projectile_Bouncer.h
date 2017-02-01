#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Bouncer : public Projectile {
public:
    Projectile_Bouncer(sf::Vector2f, sf::Vector2f);
    Projectile_Bouncer(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Bouncer(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Bouncer() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:

};
