#pragma once
#include "Globals.h"
#include "TileMap.h"
#include "Explosion.h"

class Player;

class Projectile : public sf::Drawable {
public:
    Projectile(sf::Vector2f, sf::Vector2f);
    Projectile(sf::Vector2f, sf::Vector2f, float, int, int);
    Projectile(sf::Vector2f, sf::Vector2f, float, int, int, float, int);
    virtual ~Projectile();
    virtual void Update(TileMap* &, std::vector<Player*> &, int, std::vector<Explosion*> &);
    bool IsExpired();

protected:
    virtual void PostUpdate(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
    virtual void Hit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
    virtual void PostHit(TileMap* &, std::vector<Player*> &, unsigned int, std::vector<Explosion*> &);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void PopulateVertexArray();
    bool PlayerWasHit(std::vector<Player*> &, unsigned int);

    std::vector<Projectile*> sub_projectiles;
    sf::Texture tile_textures;
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
