#include "Player.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
}

Player::Player(sf::Vector2f position) {
    is_dead = false;
    projectile_type = 0;
    angle = 40;
    power = 15;

    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(127, 127, 127, 255));
    sprite.setOutlineThickness(0);
    sprite.setFillColor(sf::Color::Green);
    sprite.setPosition(position);
}

// Main game loop calls this update function
void Player::Update(TileMap* &tileMap) {
    SetTileCoords();

    UpdateProjectiles(tileMap);
    UpdateFallingPlayer(tileMap);
    UpdateBarrel();

    window.draw(sprite);
}

// Each player has a vector of projectiles. This calls update on each projectile
void Player::UpdateProjectiles(TileMap* &tileMap) {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tileMap);

        if (projectiles[i]->IsExpired()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

// Move tank down 1 tile per frame if space exists below it
void Player::UpdateFallingPlayer(TileMap* &tileMap) {
    if (tileMap->tiles[tile_coords.x][tile_coords.y + 1].status == 0 && tileMap->tiles[tile_coords.x + 1][tile_coords.y + 1].status == 0) {
        sprite.move(0, TILE_SIZE);
    }

    if (tile_coords.x < 0 || tile_coords.x > TILES_X || tile_coords.y < 0 || tile_coords.y >= TILES_Y) {
        is_dead = true;
    }
}

// Draw the barrel on the tank
void Player::UpdateBarrel() {
    //
}

// Add a projectile to the projectile vector when fire button is pressed
void Player::InputFire() {
    sf::Vector2f position = sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y);

    switch (projectile_type) {
        case 0:
            projectiles.push_back(new Projectile(position, GetDirectionVector()));
        case 1:
            //projectiles.push_back(new );
            break;
        default:
            break;
    }
}

// Change barrel angle
void Player::InputRotate(int i) {
    if (i > 0) {
        angle += 5;
    } else {
        angle -= 5;
    }

    if (angle < 0) {
        angle += 360;
    } else if (angle >= 360) {
        angle -= 360;
    }
}

// Move player
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

// Checks if player is dead
bool Player::IsDead() {
    return is_dead;
}

// Checks if xy is on screen
bool Player::IsInBounds(sf::Vector2i v) {
    return v.x >= 0 && v.x < TILES_X && v.y >= 0 && v.y < TILES_Y - 1;
}

// Snap player to grid
void Player::SetTileCoords() {
    tile_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
}

// Get unit vector in direction based on angle and multiply by power
sf::Vector2f Player::GetDirectionVector() {
    return sf::Vector2f(sin(angle * PI_OVER_180) * power, -cos(angle * PI_OVER_180) * power);
}
