#include "Explosion.h"

Explosion::~Explosion() {}

Explosion::Explosion(sf::Vector2f p, float r) {
    life_ticks = 7;
    radius_increment = r * TILE_SIZE / life_ticks;

    sprite.setPosition(p);
    sprite.setRadius(1.0f);
}

void Explosion::Update() {
    life_ticks--;

    sprite.setPosition(sf::Vector2f(sprite.getPosition().x - radius_increment, sprite.getPosition().y - radius_increment));
    sprite.setRadius(sprite.getRadius() + radius_increment);
    window.draw(sprite);
}

bool Explosion::IsExpired() {
    return (life_ticks <= 0);
}
