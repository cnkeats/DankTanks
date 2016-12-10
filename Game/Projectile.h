#pragma once
#include "Globals.h"
#include "TileMap.h"

class Projectile {
public:
    Projectile(sf::Vector2f, sf::Vector2f);
    ~Projectile();
    void Update(TileMap* &);
    bool IsExpired();

private:
    bool IsInBounds(sf::Vector2i);

    sf::RectangleShape sprite;
    sf::Vector2f velocity;
    sf::Vector2i tile_coords;
    bool is_expired;
    float blast_radius;
};
