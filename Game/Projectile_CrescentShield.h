#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_CrescentShield : public Projectile {
public:
    Projectile_CrescentShield(sf::Vector2f, sf::Vector2f);
    Projectile_CrescentShield(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_CrescentShield(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_CrescentShield() {};
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
private:
    void CrescentHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);

    static const int STARTING_TICKS_UNTIL_SPLIT = 30;
    int ticks_until_split;
};
