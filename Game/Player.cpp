#include "Player.h"
#include "Projectile.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
}

Player::Player(sf::Vector2f position, unsigned int i) {
    is_real_time = true;
    fired = false;
    is_dead = false;
    player_index = i;
    hit_points = 100;
    power = 14;
    fuel = 1000;
    budget = 10;
    angle = 0;
    selected_projectile = 9;
    selected_projectile_cost = 0;
    selected_projectile_string = "";

    // Tank body sprite
    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(sf::Color::Black));
    sprite.setOutlineThickness(1);
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    // Tank barrel sprite
    sprite_barrel.setSize(sf::Vector2f(1, -TILE_SIZE));
    sprite_barrel.setOutlineColor(sf::Color(sf::Color::Black));
    sprite_barrel.setOutlineThickness(1);
    sprite_barrel.setFillColor(sf::Color::White);
    sprite_barrel.setPosition(sprite.getPosition());

    // Player text left column
    text_info_left.setFont(font);
    text_info_left.setCharacterSize(20);
    text_info_left.setColor(sf::Color::White);
    text_info_left.setPosition(player_index * window.getSize().x / 2, window.getSize().y - 90);

    // Player text right column
    text_info_right.setFont(font);
    text_info_right.setCharacterSize(20);
    text_info_right.setColor(sf::Color::White);
    text_info_right.setPosition(player_index * window.getSize().x / 2 + 220, window.getSize().y - 90);
}

// Main game loop calls this update function
void Player::Update(TileMap* &tileMap, std::vector<Player*> &players) {
    UpdateProjectiles(tileMap, players);
    UpdateInfo();

    if (!is_dead) {
        tile_coords = sf::Vector2i(floor(sprite.getPosition().x / TILE_SIZE), floor(sprite.getPosition().y / TILE_SIZE));

        UpdateFallingPlayer(tileMap);
        UpdateBarrel();

        window.draw(sprite);
        window.draw(sprite_barrel);
    } else {
        text_info_left.setColor(sf::Color::Red);
        text_info_right.setColor(sf::Color::Red);
    }
}

// Each player has a vector of projectiles. This calls update on each projectile
void Player::UpdateProjectiles(TileMap* &tileMap, std::vector<Player*> &players) {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tileMap, players, player_index);
        window.draw(*projectiles[i]);

        if (projectiles[i]->IsExpired()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

// Move tank down 1 tile per frame if space exists below it
void Player::UpdateFallingPlayer(TileMap* &tileMap) {
    if (tileMap->GetTile(tile_coords.x, tile_coords.y + 1).status == 0 && tileMap->GetTile(tile_coords.x + 1, tile_coords.y + 1).status == 0) {
        sprite.move(0, TILE_SIZE);
    }

    if (!IsInBounds(tile_coords)) {
        is_dead = true;
    }
}

// Draw the barrel on the tank
void Player::UpdateBarrel() {
    sprite_barrel.setPosition(sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y));
    sprite_barrel.setRotation(angle);
}

// Change power
void Player::InputPowerUp() {
    if (power < 20) {
        ++power;
    }
}

// Change power
void Player::InputPowerDown() {
    if (power > 1) {
        --power;
    }
}


// Change projectile type
void Player::InputCycleProjectileType() {
    ++selected_projectile;

    if (selected_projectile > 9) {
        selected_projectile = 0;
    }
}

// Add a projectile to the projectile vector when fire button is pressed
void Player::InputFire() {
    if (!fired || is_real_time) {
        fired = true;

        projectiles.push_back(GetProjectileData(selected_projectile).projectile);
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
    if (fuel > 0 && (!fired || is_real_time)) {
        if (tileMap->GetTile(tile_coords.x - 1, tile_coords.y).status > 0 && tileMap->GetTile(tile_coords.x - 1, tile_coords.y - 1).status == 0) {
            --fuel;
            sprite.move(-TILE_SIZE, -TILE_SIZE);
        } else if (tileMap->GetTile(tile_coords.x - 1, tile_coords.y).status == 0) {
            --fuel;
            sprite.move(-TILE_SIZE, 0);
        }
    }
}

// Move player right
void Player::InputMoveRight(TileMap* &tileMap) {
    if (fuel > 0 && (!fired || is_real_time)) {
        if (tileMap->GetTile(tile_coords.x + 2, tile_coords.y).status > 0 && tileMap->GetTile(tile_coords.x + 2, tile_coords.y - 1).status == 0) {
            --fuel;
            sprite.move(TILE_SIZE, -TILE_SIZE);
        } else if (tileMap->GetTile(tile_coords.x + 2, tile_coords.y).status == 0) {
            --fuel;
            sprite.move(TILE_SIZE, 0);
        }
    }
}

// Returns true if this player's turn is over
bool Player::IsTurnOver() {
    // Check if player fired and projectiles have expired
    if (fired && projectiles.size() == 0) {
        fired = false;
        return true;
    } else {
        return false;
    }
}

// returns true if this player is dead
bool Player::IsDead() {
    return is_dead;
}

// Returns true if this xy coordinate is in the tile map's range
bool Player::IsInBounds(sf::Vector2i v) {
    return v.x >= 0 && v.x < TILES_X && v.y >= 0 && v.y < TILES_Y - 1;
}

bool Player::IsOnTile(sf::Vector2i v) {
    return (v == tile_coords || v == sf::Vector2i(tile_coords.x + 1, tile_coords.y));
}

// Get unit vector in direction based on angle and multiply by power
sf::Vector2f Player::GetDirectionVector() {
    return sf::Vector2f(sin(angle * PI_OVER_180) * power, -cos(angle * PI_OVER_180) * power);
}

void Player::UpdateHitPoints(int damage) {
    if (!is_dead) {
        hit_points -= damage;

        if (hit_points <= 0) {
            hit_points = 0;
            is_dead = true;
        }
    }
}

// Set the player's color
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
        color = sf::Color(0, 0, 0, 255); // black with white outline
        sprite.setOutlineColor(sf::Color::White);
        sprite_barrel.setOutlineColor(sf::Color::White);
    } else {
        color = sf::Color::White;
    }

    sprite.setFillColor(color);
    sprite_barrel.setFillColor(color);
}

void Player::SetPosition(sf::Vector2i v) {
    sprite.setPosition(sf::Vector2f(v.x * TILE_SIZE, v.y * TILE_SIZE));
}

// Draw the player's info to the screen
void Player::UpdateInfo() {
    // Set string for projectile name
    selected_projectile_string = GetProjectileData(selected_projectile).name;

    // Left text
    std::string s = "Player " + ToString(player_index + 1)
                + "\n  Health: " + ToString(hit_points)
                + "\n  Power:  " + ToString(power)
                + "\n  Fuel:   " + ToString(fuel);
    text_info_left.setString(s);

    // Right text
                s = std::string("")
                + "\nProjectile: [" + ToString(selected_projectile) + "]" + selected_projectile_string
                + "\nCost:       " + ToString(selected_projectile_cost)
                + "\nDanka:      " + ToString(budget);
    text_info_right.setString(s);

    window.draw(text_info_left);
    window.draw(text_info_right);
}

ProjectileData Player::GetProjectileData(int i) {
    ProjectileData p;
    sf::Vector2f position = sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y);

    switch (selected_projectile) {
        case 0:
            p.name = "Bomb";
            p.cost = 0;
            p.projectile = new Projectile(position, GetDirectionVector());
            break;
        case 1:
            p.name = "Tile Bomb";
            p.cost = 0;
            p.projectile = new Projectile(position, GetDirectionVector(), 5, 1);
            break;
        case 2:
            p.name = "Shotgun";
            p.cost = 0;
            p.projectile = new Projectile_Shotgun(position, GetDirectionVector());
            break;
        case 3:
            p.name = "Impact Split Bomb";
            p.cost = 0;
            p.projectile = new Projectile_ImpactSplitBomb(position, GetDirectionVector());
            break;
        case 4:
            p.name = "Tunneler";
            p.cost = 0;
            p.projectile = new Projectile_Tunnel(position, GetDirectionVector(), 3, 0);
            break;
        case 5:
            p.name = "Tunneler (with shell)";
            p.cost = 0;
            p.projectile = new Projectile_Tunnel(position, GetDirectionVector());
            break;
        case 6:
            p.name = "Bridge";
            p.cost = 0;
            p.projectile = new Projectile_Bridge(position, GetDirectionVector());
            break;
        case 7:
            p.name = "Teleport";
            p.cost = 0;
            p.projectile = new Projectile_Teleport(position, GetDirectionVector());
            break;
        case 8:
            p.name = "Binary Tree";
            p.cost = 0;
            p.projectile = new Projectile_BinaryTree(position, GetDirectionVector());
            break;
        case 9:
            p.name = "Sparkler";
            p.cost = 0;
            p.projectile = new Projectile_AirSplitBomb(position, GetDirectionVector());
            break;
        default:
            p.name = "ERROR";
            p.cost = 0;
            p.projectile = new Projectile(position, GetDirectionVector());
            break;
    }

    return p;
}
