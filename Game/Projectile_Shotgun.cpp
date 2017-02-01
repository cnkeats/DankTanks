#include "Projectile_Shotgun.h"
#include "Player.h"

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 1.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 6;

    for (int i = 0; i < 6; ++i) {
        sub_projectiles.push_back(new Projectile(position, sf::Vector2f(velocity.x - cos(i), velocity.y - sin(i)), blast_radius, status_on_hit, damage / 2));
    }
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    for (int i = 0; i < 6; ++i) {
        sub_projectiles.push_back(new Projectile(position, sf::Vector2f(velocity.x - cos(i), velocity.y - sin(i)), blast_radius, status_on_hit, damage / 2));
    }
}

Projectile_Shotgun::Projectile_Shotgun(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    for (int i = 0; i < 6; ++i) {
        sub_projectiles.push_back(new Projectile(position, sf::Vector2f(velocity.x - cos(i), velocity.y - sin(i)), blast_radius, status_on_hit, damage / 2));
    }
}
