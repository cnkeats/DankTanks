#include "Player.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
}

Player::Player(sf::Vector2f position) {
    fired = false;
    is_dead = false;
    projectile_type = 0;
    angle = 0;
    power = 12;

    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(sf::Color::Black));
    sprite.setOutlineThickness(1);
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    sprite_barrel.setSize(sf::Vector2f(1, -TILE_SIZE));
    sprite_barrel.setOutlineColor(sf::Color(sf::Color::Black));
    sprite_barrel.setOutlineThickness(1);
    sprite_barrel.setFillColor(sf::Color::White);
    sprite_barrel.setPosition(sprite.getPosition());
}

// Main game loop calls this update function
void Player::Update(TileMap* &tileMap) {
    UpdateProjectiles(tileMap);

    if (!is_dead) {
        SetTileCoords();
        UpdateFallingPlayer(tileMap);
        UpdateBarrel();

        window.draw(sprite);
        window.draw(sprite_barrel);
    }
}

// Each player has a vector of projectiles. This calls update on each projectile
void Player::UpdateProjectiles(TileMap* &tileMap) {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tileMap);

        if (projectiles[i]->IsExpired()) {
            if (projectiles[i]->IsTeleportedInBounds()) {
                sprite.setPosition(projectiles[i]->GetPosition());
            }

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

    if (tile_coords.x < 0 || tile_coords.x > TILES_X || tile_coords.y < 0 || tile_coords.y >= TILES_Y - 1) {
        is_dead = true;
    }
}

// Draw the barrel on the tank
void Player::UpdateBarrel() {
    sprite_barrel.setPosition(sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y));
    sprite_barrel.setRotation(angle);
}

// Change projectile type
void Player::InputSetProjectileType(int i) {
    projectile_type = i;
}

// Add a projectile to the projectile vector when fire button is pressed
void Player::InputFire() {
    fired = true;
    sf::Vector2f position = sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y);

    switch (projectile_type) {
        case 0:
            projectiles.push_back(new Projectile_Bomb(position, GetDirectionVector(), 5.1));
            break;
        case 1:
            projectiles.push_back(new Projectile_Bomb(position, GetDirectionVector(), 12.1));
            break;
        case 2:
            for (int i = 0; i < 15; ++i) {
                projectiles.push_back(new Projectile_Bomb(position, GetDirectionVector(), 3.1));
            }
            break;
        case 3:
            projectiles.push_back(new Projectile_ImpactSplitBomb(position, GetDirectionVector()));
            break;
        case 4:
            projectiles.push_back(new Projectile_Tile(position, GetDirectionVector(), 5.1));
            break;
        case 5:
            projectiles.push_back(new Projectile_Teleport(position, GetDirectionVector()));
            break;
        case 6:
            projectiles.push_back(new Projectile_Tunnel(position, GetDirectionVector()));
            break;
        /*case 7:
            //projectiles.push_back(new Projectile_Bridge(position, GetDirectionVector()));
            break;
        case 8:
            //projectiles.push_back(new Projectile_Tile(position, GetDirectionVector(), 5.1));
            break;
        case 9:
            //projectiles.push_back(new Projectile_Tile(position, GetDirectionVector(), 5.1));
            break;*/
        default:
            //fired = false;
            break;
    }
}

// Rotate barrel clockwise
void Player::InputRotateClockwise() {
    angle += 5;

    if (angle < 0) {
        angle += 360;
    } else if (angle >= 360) {
        angle -= 360;
    }
}

// Rotate barrel counter clockwise
void Player::InputRotateCounterClockwise() {
    angle -= 5;

    if (angle < 0) {
        angle += 360;
    } else if (angle >= 360) {
        angle -= 360;
    }
}

// Move player left
void Player::InputMoveLeft(TileMap* &tileMap) {
    if (IsInBounds(sf::Vector2i(tile_coords.x - 1, tile_coords.y)) && IsInBounds(sf::Vector2i(tile_coords.x - 1, tile_coords.y - 1))) {
        if (tileMap->tiles[tile_coords.x - 1][tile_coords.y].status == 1 || tileMap->tiles[tile_coords.x - 1][tile_coords.y].status == 2) {
            if (tileMap->tiles[tile_coords.x - 1][tile_coords.y - 1].status == 0) {
                sprite.move(-TILE_SIZE, -TILE_SIZE);
            }
        } else {
            sprite.move(-TILE_SIZE, 0);
        }
    } else if (IsInBounds(sf::Vector2i(tile_coords.x - 1, tile_coords.y))) {
        if (tileMap->tiles[tile_coords.x - 1][tile_coords.y].status == 0) {
            sprite.move(-TILE_SIZE, 0);
        }
    }
}

// Move player right
void Player::InputMoveRight(TileMap* &tileMap) {
    if (IsInBounds(sf::Vector2i(tile_coords.x + 2, tile_coords.y)) && IsInBounds(sf::Vector2i(tile_coords.x + 2, tile_coords.y - 1))) {
        if (tileMap->tiles[tile_coords.x + 2][tile_coords.y].status == 1 || tileMap->tiles[tile_coords.x + 2][tile_coords.y].status == 2) {
            if (tileMap->tiles[tile_coords.x + 2][tile_coords.y - 1].status == 0) {
                sprite.move(TILE_SIZE, -TILE_SIZE);
            }
        } else {
            sprite.move(TILE_SIZE, 0);
        }
    } else if (IsInBounds(sf::Vector2i(tile_coords.x + 2, tile_coords.y))) {
        if (tileMap->tiles[tile_coords.x + 2][tile_coords.y].status == 0) {
            sprite.move(TILE_SIZE, 0);
        }
    }
}

bool Player::IsTurnOver() {
    // Check if player fired and projectiles have expired
    if (fired && projectiles.size() == 0) {
        fired = false;
        return true;
    } else {
        return false;
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

void Player::SetColor(sf::Vector2i v) {
    sf::Color color;

    // A truth table of colors!
    if (v == sf::Vector2i(0, 0)) {
        color = sf::Color(255, 255, 255, 255); // white
    } else if (v == sf::Vector2i(1, 0)) {
        color = sf::Color(255, 255, 51, 255); // yellow
    } else if (v == sf::Vector2i(2, 0)) {
        color = sf::Color(255, 51, 255, 255); // magenta
    } else if (v == sf::Vector2i(3, 0)) {
        color = sf::Color(255, 51, 51, 255); // red
    } else if (v == sf::Vector2i(0, 1)) {
        color = sf::Color(51, 255, 255, 255); // cyan
    } else if (v == sf::Vector2i(1, 1)) {
        color = sf::Color(51, 255, 51, 255); // green
    } else if (v == sf::Vector2i(2, 1)) {
        color = sf::Color(51, 51, 255, 255); // blue
    } else if (v == sf::Vector2i(3, 1)) {
        color = sf::Color(51, 51, 51, 255); // black with white outline
        sprite.setOutlineColor(sf::Color::White);
        sprite_barrel.setOutlineColor(sf::Color::White);
    } else {
        color = sf::Color::White;
    }

    sprite.setFillColor(color);
    sprite_barrel.setFillColor(color);
}

void Player::UpdateInfo() {
    //debug_string += "HP: " + toString(hitpoints);
    debug_string += "Power: " + toString(power);
    debug_string += " Angle: " + toString(angle);
    debug_string += " Projectile: " + toString(projectile_type);
    debug_string += " Projectiles: " + toString(projectiles.size());
}
