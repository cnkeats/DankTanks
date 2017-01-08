#pragma once
#include "Globals.h"

class Explosion {
public:
    Explosion(sf::Vector2f, float);
    ~Explosion();
    void Update();
    bool IsExpired();
private:
    sf::CircleShape sprite;
    int life_ticks;
    float radius_increment;
};
