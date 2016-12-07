#include "Player.h"

Player::~Player() {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        delete projectiles[i];
    }
}

Player::Player(sf::Vector2f position) {
    angle = 45;
    power = 5;

    sprite.setSize(sf::Vector2f(TILE_SIZE*2, TILE_SIZE));
    sprite.setOutlineColor(sf::Color(127, 127, 127, 255));
    sprite.setOutlineThickness(0);
    sprite.setFillColor(sf::Color::Green);
    sprite.setPosition(position);
}

void Player::Update(TileMap* &tileMap) {
    UpdateProjectiles(tileMap);

    debug_string += toString(angle);
    window.draw(sprite);
}

void Player::UpdateProjectiles(TileMap* &tileMap) {
    for (unsigned int i = 0; i < projectiles.size(); i++) {
        projectiles[i]->Update(tileMap);

        if (projectiles[i]->isExpired()) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
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

void Player::InputMove(int i) {
    if (i > 0) {
        sprite.move(sf::Vector2f(TILE_SIZE, 0));
    } else {
        sprite.move(sf::Vector2f(-TILE_SIZE, 0));
    }
}

sf::Vector2f Player::GetDirectionVector() {
    return sf::Vector2f(sin(angle * PI_OVER_180) * power, -cos(angle * PI_OVER_180) * power);
}
