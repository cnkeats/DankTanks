#include "Projectile_Shotgun.h"
#include "Player.h"

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    is_split = false;
    blast_radius = 1.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    starting_life_ticks = 30;
    damage = 6;
    life_ticks = starting_life_ticks;
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    is_split = false;
    starting_life_ticks = 30;
    life_ticks = starting_life_ticks;
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    is_split = false;
    starting_life_ticks = 30;
    life_ticks = starting_life_ticks;
}

// Overridden PostUpdate() since this projectile creates child projectiles
void Projectile_Shotgun::PostUpdate(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    if (!parent_expired && !is_split) {
        is_split = true;

        for (int i = 0; i < 6; ++i) {
            sub_projectiles.push_back(new Projectile(position, sf::Vector2f(velocity.x - cos(i), velocity.y - sin(i)), blast_radius, status_on_hit, damage / 2));
        }
    }
}
