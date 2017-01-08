#include "Projectile_ImpactSplitBomb.h"
#include "Player.h"

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 2.2;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 6;
}

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overridden PostHit() since this projectile creates child projectiles on hit
void Projectile_ImpactSplitBomb::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    for (int i = 0; i < 7; ++i) {
        sf::Vector2f rand_velocity = sf::Vector2f(rand()%8 - 4, rand()%8 - 4);
        sub_projectiles.push_back(new Projectile(position, rand_velocity, blast_radius, status_on_hit, damage / 2));
    }
}
