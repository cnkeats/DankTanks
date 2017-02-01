#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Tunnel : public Projectile {
public:
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f);
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Tunnel() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:
    int remaining_hits;
};
