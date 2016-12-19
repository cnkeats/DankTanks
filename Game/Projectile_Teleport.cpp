#include "Projectile_Teleport.h"

Projectile_Teleport::Projectile_Teleport(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 1;
}

// Overridden IsTeleportedInBounds(), normally just returns false
bool Projectile_Teleport::IsTeleportedInBounds() {
    if (IsInBounds(sf::Vector2f(GetPosition().x, GetPosition().y)) && IsInBounds(sf::Vector2f(GetPosition().x + TILE_SIZE, GetPosition().y))) {
        return true;
    } else {
        return false;
    }
}

// Overridden PostHit() since the tile_coord of the hit is moved up 1 to spawn player on top of tile
void Projectile_Teleport::PostHit(TileMap* &tileMap) {
    is_expired = true;

    --tile_coords.y;
}
