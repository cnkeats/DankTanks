#include "Projectile_Teleport.h"

Projectile_Teleport::Projectile_Teleport(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 2.1;
    status_on_hit = 0;
    blast_radius_outer = blast_radius + 1;
    status_on_hit_outer = 2;
}

Projectile_Teleport::Projectile_Teleport(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    //
}

Projectile_Teleport::Projectile_Teleport(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    //
}

// Overridden IsTeleportedInBounds(), normally just returns false
bool Projectile_Teleport::IsTeleportedInBounds(TileMap* &tileMap) {
    if (tileMap->GetTile(tile_coords.x, tile_coords.y).status >= 0 && tileMap->GetTile(tile_coords.x + 1, tile_coords.y).status >= 0) {
        return true;
    } else {
        return false;
    }
}

// Overridden PostHit() since the tile_coord of the hit is moved up 1 to spawn player on top of tile
void Projectile_Teleport::PostHit(TileMap* &tileMap) {
    --tile_coords.y;
}
