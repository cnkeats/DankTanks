#include "Player.h"
#include "Projectile.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }

    for (unsigned int i = 0; i < explosions.size(); i++) {
        delete explosions[i];
    }
}

Player::Player(unsigned int i, bool b, int color_index, sf::Vector2f position) {
    is_turn_based = b;
    is_active = !is_turn_based;
    is_dead = false;
    is_overtime = false;
    has_fired = false;
    player_index = i;
    hit_points = 100;
    power = 14;
    fuel = 100;
    budget = 4;
    angle = 0;
    shot_counter = 0;
    selected_projectile = 0;

    ProjectileData p = GetProjectileData(selected_projectile, false);
    selected_projectile_string = p.name;
    selected_projectile_cost = p.cost;

    // Tank body sprite
    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(sf::Color::Black));
    sprite.setOutlineThickness(1);
    sprite.setPosition(position);

    // Tank barrel sprite
    sprite_barrel.setSize(sf::Vector2f(1, -TILE_SIZE));
    sprite_barrel.setOutlineColor(sf::Color(sf::Color::Black));
    sprite_barrel.setOutlineThickness(1);
    sprite_barrel.setPosition(sprite.getPosition());

    SetColor(color_index);

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
void Player::Update(TileMap* &tile_map, std::vector<Player*> &players) {
    // Update projectiles
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tile_map, players, player_index, explosions);
        window.draw(*projectiles[i]);

        if (projectiles[i]->IsExpired()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }

    // Update explosions
    for (unsigned int i = 0; i < explosions.size(); i++) {
        explosions[i]->Update();
        //window.draw(*explosions[i]);

        if (explosions[i]->IsExpired()) {
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
        }
    }

    // If player is alive, update and draw it
    if (!is_dead) {
        tile_coords = sf::Vector2i(floor(sprite.getPosition().x / TILE_SIZE), floor(sprite.getPosition().y / TILE_SIZE));

        // Draw tank body (check if it falls)
        if (tile_map->GetTile(tile_coords.x, tile_coords.y + 1).status == 0 && tile_map->GetTile(tile_coords.x + 1, tile_coords.y + 1).status == 0) {
            sprite.move(0, TILE_SIZE);
        }

        if (!IsInBounds(tile_coords)) {
            is_dead = true;
        }
        window.draw(sprite);

        // Draw tank barrel
        sprite_barrel.setPosition(sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y));
        sprite_barrel.setRotation(angle);
        window.draw(sprite_barrel);
    } else {
        text_info_left.setColor(sf::Color::Red);
        text_info_right.setColor(sf::Color::Red);
    }

    // Draw player info
    // Left text
    std::string s = "Player " + ToString(player_index + 1)
                + "\n  Health: " + ToString(hit_points)
                + "\n  Power:  " + ToString(power)
                + "\n  Fuel:   " + ToString(fuel);
    text_info_left.setString(s);

    // Right text
                s = std::string("")
                + "\nProjectile: [" + ToString(selected_projectile) + "] " + selected_projectile_string
                + "\nCost:       " + ToString(selected_projectile_cost)
                + "\nDanka:      " + ToString(budget);

    if (is_overtime == true) {
        s += " (OVERTIME x2)";
    }

    if (is_active) {
        s += " (active)";
    }

    text_info_right.setString(s);

    window.draw(text_info_left);
    window.draw(text_info_right);
}

// Change player to active and give them budget for the turn
void Player::SetActive() {
    is_active = true;

    if (is_turn_based) {
        AddBudget();
    }
}

void Player::SetOvertime() {
    is_overtime = true;
}

// Change power
void Player::InputPowerUp() {
    if (is_active && power < 20) {
        ++power;
    }
}

// Change power
void Player::InputPowerDown() {
    if (is_active && power > 1) {
        --power;
    }
}

// Change projectile type
void Player::InputCycleProjectileType() {
    if (is_active) {
        ++selected_projectile;

        if (selected_projectile > 14) {
            selected_projectile = 0;
        }

        ProjectileData p = GetProjectileData(selected_projectile, false);
        selected_projectile_string = p.name;
        selected_projectile_cost = p.cost;
    }
}

// Add a projectile to the projectile vector when fire button is pressed
void Player::InputFire() {
    if (is_active) {
        ProjectileData p = GetProjectileData(selected_projectile, false);

        if (budget >= p.cost) {
            if (is_turn_based) {
                has_fired = true;
                is_active = false;
                ++shot_counter;

                if (shot_counter == 10) {
                    is_overtime = true;
                }
            }

            p = GetProjectileData(selected_projectile, true);
            projectiles.push_back(p.projectile);
            budget -= p.cost;
        }
    }
}

// Rotate barrel clockwise
void Player::InputRotateClockwise() {
    if (is_active) {
        angle += 5;

        if (angle < 0) {
            angle += 360;
        } else if (angle >= 360) {
            angle -= 360;
        }
    }
}

// Rotate barrel counter clockwise
void Player::InputRotateCounterClockwise() {
    if (is_active) {
        angle -= 5;

        if (angle < 0) {
            angle += 360;
        } else if (angle >= 360) {
            angle -= 360;
        }
    }
}

// Move player left
void Player::InputMoveLeft(TileMap* &tile_map) {
    if (is_active && fuel > 0) {
        if (tile_map->GetTile(tile_coords.x - 1, tile_coords.y).status > 0 && tile_map->GetTile(tile_coords.x - 1, tile_coords.y - 1).status == 0) {
            --fuel;
            sprite.move(-TILE_SIZE, -TILE_SIZE);
        } else if (tile_map->GetTile(tile_coords.x - 1, tile_coords.y).status == 0) {
            --fuel;
            sprite.move(-TILE_SIZE, 0);
        }
    }
}

// Move player right
void Player::InputMoveRight(TileMap* &tile_map) {
    if (is_active && fuel > 0) {
        if (tile_map->GetTile(tile_coords.x + 2, tile_coords.y).status > 0 && tile_map->GetTile(tile_coords.x + 2, tile_coords.y - 1).status == 0) {
            --fuel;
            sprite.move(TILE_SIZE, -TILE_SIZE);
        } else if (tile_map->GetTile(tile_coords.x + 2, tile_coords.y).status == 0) {
            --fuel;
            sprite.move(TILE_SIZE, 0);
        }
    }
}

// Returns true if this player's turn is over
bool Player::IsTurnOver() {
    // Check if player fired and projectiles have expired
    if (has_fired && projectiles.size() == 0) {
        has_fired = false;
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

void Player::AddBudget() {
    if (is_overtime) {
        budget += 2;
    } else {
        budget += 1;
    }

    if (budget >= 10) { // Cap of 10 budget
        budget = 10;
    }
}

void Player::SetPosition(sf::Vector2i v) {
    sprite.setPosition(sf::Vector2f(v.x * TILE_SIZE, v.y * TILE_SIZE));
}

// Set the player's color
void Player::SetColor(int i) {
    sf::Color color;

    // A truth table of colors!
    switch (i) {
        case 0:
            color = sf::Color(255, 255, 255, 255); // white
            break;
        case 1:
            color = sf::Color(255, 255, 51, 255); // yellow
            break;
        case 2:
            color = sf::Color(255, 51, 255, 255); // magenta
            break;
        case 3:
            color = sf::Color(255, 51, 51, 255); // red
            break;
        case 4:
            color = sf::Color(51, 255, 255, 255); // cyan
            break;
        case 5:
            color = sf::Color(51, 255, 51, 255); // green
            break;
        case 6:
            color = sf::Color(51, 51, 255, 255); // blue
            break;
        case 7:
            color = sf::Color(0, 0, 0, 255); // black with white outline
            sprite.setOutlineColor(sf::Color::White);
            sprite_barrel.setOutlineColor(sf::Color::White);
            break;
        default:
            color = sf::Color(255, 255, 255, 255); // white
            break;
    }

    sprite.setFillColor(color);
    sprite_barrel.setFillColor(color);
}

ProjectileData Player::GetProjectileData(int projectile_index, bool return_projectile) {
    ProjectileData p;
    sf::Vector2f position = sf::Vector2f(sprite.getPosition().x + TILE_SIZE, sprite.getPosition().y);

    switch (projectile_index) {
        // Bottom tier
        case 0:
            p.name = "Bomb";
            p.cost = 0;
            if (return_projectile) {
                p.projectile = new Projectile(position, GetDirectionVector());
            }
            break;
        case 1:
            p.name = "Tile Bomb";
            p.cost = 0;
            if (return_projectile) {
                p.projectile = new Projectile(position, GetDirectionVector(), 3.2, 1, 10);
            }
            break;

        // Low tier
        case 2:
            p.name = "Shotgun";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_Shotgun(position, GetDirectionVector());
            }
            break;
        case 3:
            p.name = "Impact Split Bomb";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_ImpactSplitBomb(position, GetDirectionVector());
            }
            break;
        case 4:
            p.name = "Tunneler";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_Tunnel(position, GetDirectionVector(), 3.2, 0, 3);
            }
            break;
        case 5:
            p.name = "Bridge";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_Bridge(position, GetDirectionVector());
            }
            break;
        case 6:
            p.name = "Boomerang";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_Boomerang(position, GetDirectionVector());
            }
            break;
        case 7:
            p.name = "Bouncer";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_Bouncer(position, GetDirectionVector());
            }
            break;
        case 8:
            p.name = "Crescent Shield";
            p.cost = 2;
            if (return_projectile) {
                p.projectile = new Projectile_CrescentShield(position, GetDirectionVector());
            }
            break;

        // Mid tier
        case 9:
            p.name = "Tunneler (with shell)";
            p.cost = 6;
            if (return_projectile) {
                p.projectile = new Projectile_Tunnel(position, GetDirectionVector());
            }
            break;
        case 10:
            p.name = "Teleport";
            p.cost = 6;
            if (return_projectile) {
                p.projectile = new Projectile_Teleport(position, GetDirectionVector());
            }
            break;

        // Top tier
        case 11:
            p.name = "Binary Tree";
            p.cost = 10;
            if (return_projectile) {
                p.projectile = new Projectile_BinaryTree(position, GetDirectionVector());
            }
            break;
        case 12:
            p.name = "Sparkler";
            p.cost = 10;
            if (return_projectile) {
                p.projectile = new Projectile_AirSplitBomb(position, GetDirectionVector());
            }
            break;
        case 13:
            p.name = "Cardinal";
            p.cost = 10;
            if (return_projectile) {
                p.projectile = new Projectile_Cardinal(position, GetDirectionVector());
            }
            break;

        // Coming soon
        case 14:
            p.name = "Digger";
            p.cost = 6;
            if (return_projectile) {
                p.projectile = new Projectile_Digger(position, GetDirectionVector());
            }
            break;
        default:
            p.name = "ERROR";
            p.cost = 0;
            if (return_projectile) {
                p.projectile = new Projectile(position, GetDirectionVector());
            }
            break;
    }

    // Debug, 0 cost for all
    //p.cost = 0;

    return p;
}
