#include "Projectile_Bomb.h"

Projectile_Bomb::Projectile_Bomb(sf::Vector2f position, sf::Vector2f angle, float r) : Projectile(position, angle) {
    blast_radius = r;
}
