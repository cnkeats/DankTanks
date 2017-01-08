#include "Projectile_Bridge.h"
#include "Player.h"

Projectile_Bridge::Projectile_Bridge(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 1;
    status_on_hit = 2;
    damage = 1;
}

Projectile_Bridge::Projectile_Bridge(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_Bridge::Projectile_Bridge(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overridden PostHit() since this projectile creates child projectiles on hit
void Projectile_Bridge::PostHit(TileMap* &tileMap, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    int bridge_length = TILES_X;
    int bridge_height = 1;
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
