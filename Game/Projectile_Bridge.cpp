#include "Projectile_Bridge.h"

Projectile_Bridge::Projectile_Bridge(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 1;
    status_on_hit = 2;
}

Projectile_Bridge::Projectile_Bridge(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    //
}

Projectile_Bridge::Projectile_Bridge(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    //
}

// Overridden PostHit() since this projectile creates child projectiles on hit
void Projectile_Bridge::PostHit(TileMap* &tileMap) {
    int bridge_length = 100;

    if (velocity.x >= 0) { // projectile moving right
        for (int x = tile_coords.x; x > tile_coords.x - bridge_length; --x) {
            sf::Vector2i p = sf::Vector2i(x, tile_coords.y);

            if (IsInBounds(p)) {
                if (tileMap->tiles[p.x][p.y].status != 0 && x < tile_coords.x - 2) {
                    break;
                }
                tileMap->UpdateStatus(p, 2);
            }
        }
    } else { // projectile moving left
        for (int x = tile_coords.x; x < tile_coords.x + bridge_length; ++x) {
            sf::Vector2i p = sf::Vector2i(x, tile_coords.y);

            if (IsInBounds(p)) {
                if (tileMap->tiles[p.x][p.y].status != 0 && x > tile_coords.x + 2) {
                    break;
                }
                tileMap->UpdateStatus(p, 2);
            }
        }
    }
}
