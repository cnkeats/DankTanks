#include "Projectile.h"

Projectile::~Projectile() {}

Projectile::Projectile() {
    sprite.setSize(sf::Vector2f(4, 4));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(100, 160);

    velocity = sf::Vector2f(3.0f, 0.0f);
}

void Projectile::Update(sf::RenderWindow &window, TileMap* &tileMap) {
    grid_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
    //debug_string += "(" + toString(grid_coords.x) + " " + toString(grid_coords.y) + ")";

    if (isInBounds(grid_coords)) {
        velocity.x += tileMap->vector_field[grid_coords.x][grid_coords.y].x;
        velocity.y += tileMap->vector_field[grid_coords.x][grid_coords.y].y;
    }

    sprite.move(velocity.x, velocity.y);

    // bounce
    if (sprite.getPosition().x < 0 || sprite.getPosition().x > window.getSize().x) {
        velocity.x *= -1;
    }

    if (sprite.getPosition().y < 0 || sprite.getPosition().y > window.getSize().y) {
        velocity.y *= -1;
    }

    window.draw(sprite);
}

bool Projectile::isInBounds(sf::Vector2i grid_coords) {
    return grid_coords.x >= 0 && grid_coords.x < TILES_X && grid_coords.y >= 0 && grid_coords.y < TILES_Y;
}
