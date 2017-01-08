#include "Projectile_Boomerang.h"
#include "Player.h"

Projectile_Boomerang::Projectile_Boomerang(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 4.2;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 20;
    original_velocity = velocity;
}

Projectile_Boomerang::Projectile_Boomerang(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    original_velocity = velocity;
}

Projectile_Boomerang::Projectile_Boomerang(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    original_velocity = velocity;
}

void Projectile_Boomerang::PostUpdate(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    if (starting_life_ticks - life_ticks > 30) {
        velocity.x -= original_velocity.x / 50;
    }
}
