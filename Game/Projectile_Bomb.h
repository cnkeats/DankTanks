#pragma once
#include "Globals.h"
#include "TileMap.h"
#include "Projectile.h"

class Projectile_Bomb : public Projectile {
public:
    Projectile_Bomb(sf::Vector2f, sf::Vector2f, float);
    ~Projectile_Bomb();
private:

};
