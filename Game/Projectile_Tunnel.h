#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Tunnel : public Projectile {
public:
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f);
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f, float, int);
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile_Tunnel() {};
    virtual void PostHit(TileMap* &, std::vector<Player*> &, int);
private:

};
