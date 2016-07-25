#pragma once
#include "Globals.h"
#include "TileMap.h"

class Projectile {
public:
    Projectile(sf::Vector2f, sf::Vector2f);
    Projectile(sf::Vector2f, sf::Vector2f, float, int);
    Projectile(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile();
    virtual void Update(TileMap* &);
    virtual bool IsTeleportedInBounds(TileMap* &);
    bool IsExpired();
    sf::Vector2f GetPosition();

protected:
    virtual void PostUpdate(TileMap* &);
    virtual void Hit(TileMap* &);
    virtual void PostHit(TileMap* &);

    std::vector<Projectile*> sub_projectiles;
    sf::RectangleShape sprite;
    sf::Vector2f velocity;
    sf::Vector2i tile_coords;
    float blast_radius;
    float blast_radius_outer;
    int status_on_hit;
    int status_on_hit_outer;
    bool parent_expired;
    bool children_expired;
};
