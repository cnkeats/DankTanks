#include "Projectile_Bridge.h"
#include "Player.h"

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
void Projectile_Bridge::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index) {
    int bridge_length = TILES_X;
    int bridge_height = 3;
    int direction = 1;

    if (velocity.x >= 0) { // projectile moving right
        direction = -1;
    } else { // projectile moving left
        direction = 1;
    }

    for (int y = 0; y < bridge_height; ++y) {
        for (int x = 0; x < bridge_length; ++x) {
            sf::Vector2i p = sf::Vector2i(tile_coords.x + direction * x, tile_coords.y - y);

            if (direction == -1 && tileMap->GetTile(p.x, p.y).status > 0 && p.x < tile_coords.x - 2) {
                break;
            } else if (direction == 1 && tileMap->GetTile(p.x, p.y).status > 0 && p.x > tile_coords.x + 2) {
                break;
            }
            tileMap->WriteStatus(p, 2);
        }
    }
}
