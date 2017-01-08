#include "Projectile_CrescentShield.h"
#include "Player.h"

Projectile_CrescentShield::Projectile_CrescentShield(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 8.2;
    status_on_hit = 2;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 6;
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_CrescentShield::Projectile_CrescentShield(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_CrescentShield::Projectile_CrescentShield(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

// Overridden PostUpdate() since this projectile creates child projectiles over time
void Projectile_CrescentShield::PostUpdate(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    --ticks_until_split;

    if (ticks_until_split <= 0) {
        parent_expired = true;
    } else if (ticks_until_split == 1) {
        Hit(tile_map, players, owner_index, explosions);

        float denom = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        sf::Vector2f unit_vector;
        unit_vector.x = velocity.x / denom;
        unit_vector.y = velocity.y / denom;

        sf::Vector2f sub_position;
        sub_position.x = position.x - blast_radius * TILE_SIZE / 2 * unit_vector.x;
        sub_position.y = position.y - blast_radius * TILE_SIZE / 2 * unit_vector.y;
        sub_projectiles.push_back(new Projectile(sub_position, sf::Vector2f(0, 0), blast_radius, 0, 0));
    }
}
