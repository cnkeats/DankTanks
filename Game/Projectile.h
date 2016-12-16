#pragma once
#include "Globals.h"
#include "TileMap.h"

class Projectile {
public:
    Projectile(sf::Vector2f, sf::Vector2f);
    ~Projectile();
    virtual void Update(TileMap* &);
    virtual bool IsTeleportedInBounds();
    bool IsExpired();
    sf::Vector2f GetPosition();

protected:
    virtual void Hit(TileMap* &);
    virtual void PostHit(TileMap* &);
    bool IsInBounds(sf::Vector2i);
    bool IsInBounds(sf::Vector2f);

    sf::RectangleShape sprite;
    sf::Vector2f velocity;
    sf::Vector2i tile_coords;
    bool is_expired;
    float blast_radius;
    int status_on_hit;
};
