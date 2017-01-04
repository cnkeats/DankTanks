#include "Projectile_AirSplitBomb.h"
#include "Player.h"

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
    blast_radius = 5;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
}

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_AirSplitBomb::Projectile_AirSplitBomb(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

// Overridden PostUpdate() since this projectile creates child projectiles over time
void Projectile_AirSplitBomb::PostUpdate(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    if (!parent_expired) {
        --ticks_until_split;

        if (ticks_until_split <= 0) {
            ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;

            if (velocity.x >= 0) {
                sf::Vector2f rand_velocity = sf::Vector2f(rand()%4, rand()%8 - 4);
                sub_projectiles.push_back(new Projectile(position, rand_velocity, 2.1, status_on_hit));
            } else {
                sf::Vector2f rand_velocity = sf::Vector2f(rand()%4 - 4, rand()%8 - 4);
                sub_projectiles.push_back(new Projectile(position, rand_velocity, 2.1, status_on_hit));
            }
        }
    }
}
