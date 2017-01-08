#include "Projectile_Digger.h"
#include "Player.h"

Projectile_Digger::Projectile_Digger(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 2.2;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 6;
}

Projectile_Digger::Projectile_Digger(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_Digger::Projectile_Digger(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overridden PostHit()
void Projectile_Digger::PostUpdate(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    // TODO
}

// Overridden PostHit()
void Projectile_Digger::PostHit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    // TODO
}
