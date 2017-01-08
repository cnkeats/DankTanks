#include "Projectile_Cardinal.h"
#include "Player.h"

Projectile_Cardinal::Projectile_Cardinal(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 1;
    status_on_hit = 0;
    damage = 20;
}

Projectile_Cardinal::Projectile_Cardinal(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_Cardinal::Projectile_Cardinal(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overridden PostHit()
void Projectile_Cardinal::PostHit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    int inner = 2;
    int outer = 3;

    for (int x = 0; x < TILES_X; ++x) { // Border
        tile_map->WriteStatus(sf::Vector2i(x, tile_coords.y + outer), 2);
        tile_map->WriteStatus(sf::Vector2i(x, tile_coords.y - outer), 2);
    }

    for (int y = 0; y < TILES_Y; ++y) { // Border
        tile_map->WriteStatus(sf::Vector2i(tile_coords.x + outer, y), 2);
        tile_map->WriteStatus(sf::Vector2i(tile_coords.x - outer, y), 2);
    }

    for (int x = 0; x < TILES_X; ++x) {
        for (int y = tile_coords.y - inner; y <= tile_coords.y + inner; ++y) {
            sf::Vector2i p = sf::Vector2i(x, y);

            for (unsigned int i = 0; i < players.size(); ++i) { // Core
                if (players[i]->IsOnTile(p)) { // Player is on this tile
                    players[i]->UpdateHitPoints(damage);
                }
            }

            tile_map->WriteStatus(p, status_on_hit);
        }
    }

    for (int x = tile_coords.x - inner; x <= tile_coords.x + inner; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            sf::Vector2i p = sf::Vector2i(x, y);

            for (unsigned int i = 0; i < players.size(); ++i) { // Core
                if (players[i]->IsOnTile(p)) { // Player is on this tile
                    players[i]->UpdateHitPoints(damage);
                }
            }

            tile_map->WriteStatus(p, status_on_hit);
        }
    }
}
