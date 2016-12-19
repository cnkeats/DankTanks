#include "Projectile_Tunnel.h"

Projectile_Tunnel::Projectile_Tunnel(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    //
}

// Overriden PostHit() since this projectile creates on tunnel on hit, not a normal circle
void Projectile_Tunnel::PostHit(TileMap* &tileMap) {
    is_expired = true;
    int tunnel_length = 35;
    int tunnel_height = 8;

    if (velocity.x >= 0) {
        for (int x = tile_coords.x - 5; x < tile_coords.x + tunnel_length; ++x) {
            for (int y = tile_coords.y - 5; y < tile_coords.y + tunnel_height; ++y) {
                sf::Vector2i position = sf::Vector2i(x, y);

                if (IsInBounds(position)) {
                    if ((y == tile_coords.y - 5 || y == tile_coords.y + tunnel_height - 1) && tileMap->tiles[x][y].status != 0) {
                        tileMap->UpdateStatus(position, 2);
                    } else if (y == TILES_Y - 1) {
                        tileMap->UpdateStatus(position, 2);
                    } else {
                        tileMap->UpdateStatus(position, 0);
                    }
                }
            }
        }
    } else {
        for (int x = tile_coords.x + 5; x > tile_coords.x - tunnel_length; --x) {
            for (int y = tile_coords.y + 5; y > tile_coords.y - tunnel_height; --y) {
                sf::Vector2i position = sf::Vector2i(x, y);

                if (IsInBounds(position)) {
                    if ((y == tile_coords.y + 5 || y == tile_coords.y - tunnel_height + 1) && tileMap->tiles[x][y].status != 0) {
                        tileMap->UpdateStatus(position, 2);
                    } else if (y == TILES_Y - 1) {
                        tileMap->UpdateStatus(position, 2);
                    } else {
                        tileMap->UpdateStatus(position, 0);
                    }
                }
            }
        }
    }
}
