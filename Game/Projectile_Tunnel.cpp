#include "Projectile_Tunnel.h"
#include "Player.h"

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 3.2;
    status_on_hit = 0;
    blast_radius_outer = blast_radius + 1;
    status_on_hit_outer = 2;
    damage = 4;
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overriden PostHit() since this projectile creates on tunnel on hit, not a normal circle
void Projectile_Tunnel::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    for (int i = 0; i < 5; ++i) {
        sub_projectiles.push_back(new Projectile(position, velocity, blast_radius, status_on_hit, damage, blast_radius_outer, status_on_hit_outer));
    }

    // Stronger projectile at the very end
    sub_projectiles.push_back(new Projectile(position, velocity, blast_radius * 2, status_on_hit, damage * 2, blast_radius_outer, status_on_hit_outer));
}
