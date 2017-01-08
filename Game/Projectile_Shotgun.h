#pragma once
#include "Globals.h"
#include "Projectile.h"

class Projectile_Shotgun : public Projectile {
public:
    Projectile_Shotgun(sf::Vector2f, sf::Vector2f);
    Projectile_Shotgun(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile_Shotgun(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile_Shotgun() {};
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, unsigned int);
private:
    bool is_split;
};
