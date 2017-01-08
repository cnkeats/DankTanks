#include "Projectile_Teleport.h"
#include "Player.h"

Projectile_Teleport::Projectile_Teleport(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 2.4;
    status_on_hit = 0;
    blast_radius_outer = blast_radius + 1;
    status_on_hit_outer = 2;
    damage = 10;
}

Projectile_Teleport::Projectile_Teleport(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    //
}

Projectile_Teleport::Projectile_Teleport(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    //
}

// Overridden PostHit() since the tile_coord of the hit is moved up 1 to spawn player on top of tile
void Projectile_Teleport::PostHit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    --tile_coords.y;

    if (tile_map->GetTile(tile_coords.x, tile_coords.y).status >= 0 && tile_map->GetTile(tile_coords.x + 1, tile_coords.y).status >= 0) {
        players[owner_index]->SetPosition(tile_coords);
    }
}
