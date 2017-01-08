#include "Projectile_Tunnel.h"
#include "Player.h"

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 3.2;
    status_on_hit = 0;
    blast_radius_outer = blast_radius + 1;
    status_on_hit_outer = 2;
    damage = 4;
    remaining_hits = 8;
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    remaining_hits = 8;
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    remaining_hits = 8;
}

// Overriden PostHit()
void Projectile_Tunnel::PostHit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    --remaining_hits;

    if (remaining_hits > 0) {
        parent_expired = false;
    }
}
