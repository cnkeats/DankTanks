#include "Projectile.h"

Projectile::~Projectile() {}

Projectile::Projectile(sf::Vector2f position, sf::Vector2f angle) {
    sprite.setSize(sf::Vector2f(2, 2));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    velocity = angle;
    blast_radius = 25;

    is_expired = false;
}

void Projectile::Update(TileMap* &tileMap) {
    tile_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
    //debug_string += "(" + toString(tile_coords.x) + " " + toString(tile_coords.y) + ")";

    if (isInBounds(tile_coords)) {
        if (tileMap->tiles[tile_coords.x][tile_coords.y].status == 0) {
            // Add velocity from vector field
            velocity.x += tileMap->tiles[tile_coords.x][tile_coords.y].velocity.x;
            velocity.y -= tileMap->tiles[tile_coords.x][tile_coords.y].velocity.y;

            // Move sprite
            sprite.move(velocity.x, velocity.y);

            // Draw sprite to screen
            window.draw(sprite);
        } else { // Hit!
            tileMap->UpdateStatus(tile_coords, 0);

            for (int x = -blast_radius; x <= blast_radius; ++x) {
                for (int y = -blast_radius; y <= blast_radius; ++y) {
                    sf::Vector2i p = sf::Vector2i(tile_coords.x + x, tile_coords.y + y);

                    if (isInBounds(p) && x*x + y*y < blast_radius*blast_radius) {
                        tileMap->UpdateStatus(p, 0);
                    }
                }
            }

            is_expired = true;
        }
    } else {
        is_expired = true;
    }
}

bool Projectile::isInBounds(sf::Vector2i v) {
    return v.x >= 0 && v.x < TILES_X && v.y >= 0 && v.y < TILES_Y;
}

bool Projectile::isExpired() {
    return is_expired;
}
