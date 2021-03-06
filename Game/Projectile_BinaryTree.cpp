#include "Projectile_BinaryTree.h"
#include "Player.h"

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f p, sf::Vector2f v) : Projectile(p, v) {
    blast_radius = 2.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    damage = 6;
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) : Projectile(p, v, r, s, d) {
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

Projectile_BinaryTree::Projectile_BinaryTree(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) : Projectile(p, v, r, s, d, r2, s2) {
    starting_life_ticks = 300;
    life_ticks = starting_life_ticks;
    ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;
}

// Overridden PostUpdate()
void Projectile_BinaryTree::PostUpdate(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    if (!parent_expired) {
        --ticks_until_split;

        if (ticks_until_split <= 0) {
            ticks_until_split = STARTING_TICKS_UNTIL_SPLIT;

            if (velocity.x >= 0) {
                sub_projectiles.push_back(new Projectile_BinaryTree(position, sf::Vector2f(velocity.x + 1, velocity.y - 0.1), blast_radius, status_on_hit, damage));
            } else {
                sub_projectiles.push_back(new Projectile_BinaryTree(position, sf::Vector2f(velocity.x - 1, velocity.y - 0.1), blast_radius, status_on_hit, damage));
            }
        }
    }
}
