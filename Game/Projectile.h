#pragma once
#include "Globals.h"
#include "TileMap.h"

class Player;

class Projectile : public sf::Drawable {
public:
    Projectile(sf::Vector2f, sf::Vector2f);
    Projectile(sf::Vector2f, sf::Vector2f, float, int);
    Projectile(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile();
    virtual void Update(TileMap* &, std::vector<Player*> &, int);
    bool IsExpired();

protected:
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, int);
    virtual void Hit(TileMap* &, std::vector<Player*> &, int);
    virtual void PostHit(TileMap* &, std::vector<Player*> &, int);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void PopulateVertexArray();
    bool PlayerWasHit(std::vector<Player*> &);

    std::vector<Projectile*> sub_projectiles;
    sf::VertexArray vertices;
    sf::Vector2f velocity;
    sf::Vector2f position;
    sf::Vector2i tile_coords;
    float blast_radius;
    float blast_radius_outer;
    int status_on_hit;
    int status_on_hit_outer;
    int life_ticks;
    int starting_life_ticks;
    int damage;
    bool parent_expired;
    bool children_expired;
};
