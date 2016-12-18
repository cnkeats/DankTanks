#include "Projectile_Teleport.h"

Projectile_Teleport::Projectile_Teleport(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 1;
}

bool Projectile_Teleport::IsTeleportedInBounds() {
    if (IsInBounds(sf::Vector2f(GetPosition().x, GetPosition().y)) && IsInBounds(sf::Vector2f(GetPosition().x + TILE_SIZE, GetPosition().y))) {
        return true;
    } else {
        return false;
    }
}

void Projectile_Teleport::PostHit(TileMap* &tileMap) {
    is_expired = true;

    --tile_coords.y;
}
