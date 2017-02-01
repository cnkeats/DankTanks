#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Digger : public Projectile {
public:
    Projectile_Digger(sf::Vector2f, sf::Vector2f);
    Projectile_Digger(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Digger(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Digger() {};
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:

};
