#include "Projectile.h"

Projectile::~Projectile() {}

Projectile::Projectile() {
    sprite.setSize(sf::Vector2f(2, 2));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(100, 500);

    velocity = sf::Vector2f(5.0f, -5.0f);

    is_expired = false;
}

void Projectile::Update(sf::RenderWindow &window, TileMap* &tileMap) {
    tile_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
    //debug_string += "(" + toString(tile_coords.x) + " " + toString(tile_coords.y) + ")";

    if (isInBounds()) {
        if (tileMap->tiles[tile_coords.x][tile_coords.y].status == 0) {
            // Add velocity from vector field
            velocity.x += tileMap->tiles[tile_coords.x][tile_coords.y].velocity.x;
            velocity.y -= tileMap->tiles[tile_coords.x][tile_coords.y].velocity.y;

            // Move sprite
            sprite.move(velocity.x, velocity.y);

            // Draw sprite to screen
            window.draw(sprite);
        } else { // Hit!
            //TODO border check
            tileMap->tiles[tile_coords.x][tile_coords.y].status = 0;
            tileMap->tiles[tile_coords.x+1][tile_coords.y].status = 0;
            tileMap->tiles[tile_coords.x][tile_coords.y+1].status = 0;
            tileMap->tiles[tile_coords.x-1][tile_coords.y].status = 0;
            tileMap->tiles[tile_coords.x][tile_coords.y-1].status = 0;

            is_expired = true;
        }
    } else {
        is_expired = true;
    }
}

bool Projectile::isInBounds() {
    return tile_coords.x >= 0 && tile_coords.x < TILES_X && tile_coords.y >= 0 && tile_coords.y < TILES_Y;
}

bool Projectile::isExpired() {
    return is_expired;
}
