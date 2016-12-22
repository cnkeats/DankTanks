#include "Projectile_BinaryTree.h"

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f position, sf::Vector2f angle) : Projectile(position, angle) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
    blast_radius = 2.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
}

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f position, sf::Vector2f angle, float radius, int status) : Projectile(position, angle, radius, status) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) : Projectile(position, angle, radius, status, radius2, status2) {
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

// Overridden PostUpdate() since this projectile creates child projectiles over time
void Projectile_BinaryTree::PostUpdate(TileMap* &tileMap) {
    if (!is_split) {
        --ticks_until_split;

        if (ticks_until_split <= 0) {
            ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
            is_split = true;

            sub_projectiles.push_back(new Projectile_BinaryTree(sprite.getPosition(), velocity, blast_radius, status_on_hit));
            sub_projectiles.push_back(new Projectile_BinaryTree(sprite.getPosition(), sf::Vector2f(velocity.x + 1, velocity.y - 0.1), blast_radius, status_on_hit));
        }
    }
}
