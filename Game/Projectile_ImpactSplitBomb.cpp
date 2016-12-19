#include "Projectile_ImpactSplitBomb.h"

Projectile_ImpactSplitBomb::Projectile_ImpactSplitBomb(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    blast_radius = 5.1;
    is_split = false;
}

// Overridden Update() since this projectile has child projectiles
void Projectile_ImpactSplitBomb::Update(TileMap* &tileMap) {
    if (!is_split) { // Didn't split yet, update main projectile
        Projectile::Update(tileMap);
    } else if (sub_projectiles.size() > 0) { // Did split and still has sub_projectiles
        is_expired = false;
        for (unsigned int i = 0; i < sub_projectiles.size(); i++) {
            sub_projectiles[i]->Update(tileMap);

            if (sub_projectiles[i]->IsExpired()) {
                delete sub_projectiles[i];
                sub_projectiles.erase(sub_projectiles.begin() + i);
            }
        }
    } else { // Did split and has no sub_projectiles
        is_expired = true;
    }
}

// Overridden PostHit() since this projectile creates child projectiles on hit
void Projectile_ImpactSplitBomb::PostHit(TileMap* &tileMap) {
    is_split = true;

    for (int i = 0; i < 7; ++i) {
        sf::Vector2f rand_velocity = sf::Vector2f(rand()%8 - 4, rand()%8 - 4);
        sub_projectiles.push_back(new Projectile_Bomb(sprite.getPosition(), rand_velocity, 3.1));
    }
}
