#include "Projectile_AirSplitBomb.h"
#include "Player.h"

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
    blast_radius = 5.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 10;
}

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

// Overridden PostUpdate() since this projectile creates child projectiles over time
void Projectile_AirSplitBomb::PostUpdate(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    if (!parent_expired) {
        --ticks_until_split;

        if (ticks_until_split <= 0) {
            ticks_until_split = 2;

            if (velocity.x >= 0) {
                sf::Vector2f rand_velocity = sf::Vector2f(rand()%4, rand()%8 - 4);
                sub_projectiles.push_back(new Projectile(position, rand_velocity, 2.4, status_on_hit, damage / 2));
            } else {
                sf::Vector2f rand_velocity = sf::Vector2f(rand()%4 - 4, rand()%8 - 4);
                sub_projectiles.push_back(new Projectile(position, rand_velocity, 2.4, status_on_hit, damage / 2));
            }
        }
    }
}
