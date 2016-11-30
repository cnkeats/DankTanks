#include "Projectile.h"

Projectile::~Projectile() {}

Projectile::Projectile() {
    sprite.setSize(sf::Vector2f(4, 4));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(100, 100);

    velocity = sf::Vector2f(2, -5);
}

void Projectile::Update(sf::RenderWindow &window) {
    velocity.y += 9.8/60;

    sprite.move(velocity.x, velocity.y);

    // bounce
    if (sprite.getPosition().y > window.getSize().y) {
        velocity.y *= -1;
    }

    window.draw(sprite);
}
