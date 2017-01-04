#include "Projectile_Shotgun.h"
#include "Player.h"

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    is_split = false;
    blast_radius = 2;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    starting_life_ticks = 30;
    life_ticks = starting_life_ticks;
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    is_split = false;
    starting_life_ticks = 30;
    life_ticks = starting_life_ticks;
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    is_split = false;
    starting_life_ticks = 30;
    life_ticks = starting_life_ticks;
}

// Overridden PostUpdate() since this projectile creates child projectiles
void Projectile_Shotgun::PostUpdate(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    if (!parent_expired && !is_split) {
        is_split = true;

        for (int i = 0; i <= 5; ++i) {
            sub_projectiles.push_back(new Projectile(position, sf::Vector2f(velocity.x - cos(i), velocity.y - sin(i)), blast_radius, status_on_hit));
        }
    }
}
