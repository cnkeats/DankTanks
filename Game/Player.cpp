#include "Player.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
}

Player::Player(sf::Vector2f position) {
    is_dead = false;
    angle = 45;
    power = 10;

    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(127, 127, 127, 255));
    sprite.setOutlineThickness(0);
    sprite.setFillColor(sf::Color::Green);
    sprite.setPosition(position);
}

void Player::Update(TileMap* &tileMap) {
    SetTileCoords();

    UpdateProjectiles(tileMap);
    UpdatePosition(tileMap);

    window.draw(sprite);
}

void Player::UpdateProjectiles(TileMap* &tileMap) {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tileMap);

        if (projectiles[i]->IsExpired()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

void Player::UpdatePosition(TileMap* &tileMap) {
    if (tileMap->tiles[tile_coords.x][tile_coords.y + 1].status == 0 && tileMap->tiles[tile_coords.x + 1][tile_coords.y + 1].status == 0) {
        sprite.move(0, TILE_SIZE);
    }

    if (tile_coords.x < 0 || tile_coords.x > TILES_X || tile_coords.y < 0 || tile_coords.y >= TILES_Y) {
        is_dead = true;
    }
}

void Player::InputFire(int i) {
    sf::Vector2f position = sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y);

    switch (i) {
    case 0:
        projectiles.push_back(new Projectile(position, GetDirectionVector()));
    case 1:
        //projectiles.push_back(new );
        break;
    default:
        break;
    }
}

void Player::InputRotate(int i) {
    if (i > 0) {
        angle += 10;
    } else {
        angle -= 10;
    }

    if (angle < 0) {
        angle += 360;
    } else if (angle >= 360) {
        angle -= 360;
    }
}

void Player::InputMove(TileMap* &tileMap, int i) {
    // TODO Make this prettier
    if (i > 0) {
        if (IsInBounds(sf::Vector2i(tile_coords.x + 2, tile_coords.y)) && IsInBounds(sf::Vector2i(tile_coords.x + 2, tile_coords.y - 1))) {
            if (tileMap->tiles[tile_coords.x + 2][tile_coords.y].status == 1) {
                if (tileMap->tiles[tile_coords.x + 2][tile_coords.y - 1].status == 0) {
                    sprite.move(TILE_SIZE, -TILE_SIZE);
                }
            } else {
                sprite.move(TILE_SIZE, 0);
            }
        }
    } else {
        if (IsInBounds(sf::Vector2i(tile_coords.x - 1, tile_coords.y)) && IsInBounds(sf::Vector2i(tile_coords.x - 1, tile_coords.y - 1))) {
            if (tileMap->tiles[tile_coords.x - 1][tile_coords.y].status == 1) {
                if (tileMap->tiles[tile_coords.x - 1][tile_coords.y - 1].status == 0) {
                    sprite.move(-TILE_SIZE, -TILE_SIZE);
                }
            } else {
                sprite.move(-TILE_SIZE, 0);
            }
        }
    }
}

bool Player::IsDead() {
    return is_dead;
}

bool Player::IsInBounds(sf::Vector2i v) {
    return v.x >= 0 && v.x < TILES_X && v.y >= 0 && v.y < TILES_Y - 1;
}

void Player::SetTileCoords() {
    tile_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
}

sf::Vector2f Player::GetDirectionVector() {
    return sf::Vector2f(sin(angle * PI_OVER_180) * power, -cos(angle * PI_OVER_180) * power);
}
