#include "Projectile_ImpactSplitBomb.h"
#include "Player.h"

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 3;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
}

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    //
}

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    //
}

// Overridden PostHit() since this projectile creates child projectiles on hit
void Projectile_ImpactSplitBomb::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    for (int i = 0; i < 7; ++i) {
        sf::Vector2f rand_velocity = sf::Vector2f(rand()%8 - 4, rand()%8 - 4);
        sub_projectiles.push_back(new Projectile(position, rand_velocity, blast_radius, status_on_hit));
    }
}
