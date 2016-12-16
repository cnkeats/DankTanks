#include "Projectile_Tile.h"

Projectile_Tile::Projectile_Tile(sf::Vector2f position, sf::Vector2f angle, float r) : Projectile(position, angle) {
    blast_radius = r;
    status_on_hit = 1;
}
