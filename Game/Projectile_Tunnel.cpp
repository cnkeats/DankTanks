#include "Projectile_Tunnel.h"
#include "Player.h"

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 3;
    status_on_hit = 0;
    blast_radius_outer = blast_radius + 1;
    status_on_hit_outer = 2;
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    //
}

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    //
}

// Overriden PostHit() since this projectile creates on tunnel on hit, not a normal circle
void Projectile_Tunnel::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    for (int i = 0; i < 10; ++i) {
        sub_projectiles.push_back(new Projectile(position, velocity, blast_radius, status_on_hit, blast_radius_outer, status_on_hit_outer));
    }
}
