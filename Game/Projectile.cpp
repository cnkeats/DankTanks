#include "Projectile.h"

Projectile::~Projectile() {
    for (unsigned int i = 0; i < sub_projectiles.size(); i++) {
        delete sub_projectiles[i];
    }
}

Projectile::Projectile(sf::Vector2f position, sf::Vector2f angle) {
    sprite.setSize(sf::Vector2f(2, 2));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    velocity = angle;
    blast_radius = 5.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;
}

Projectile::Projectile(sf::Vector2f position, sf::Vector2f angle, float radius, int status) {
    sprite.setSize(sf::Vector2f(2, 2));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    velocity = angle;
    blast_radius = radius;
    status_on_hit = status;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;
}

Projectile::Projectile(sf::Vector2f position, sf::Vector2f angle, float radius, int status, float radius2, int status2) {
    sprite.setSize(sf::Vector2f(2, 2));
    sprite.setFillColor(sf::Color::White);
    sprite.setPosition(position);

    velocity = angle;
    blast_radius = radius;
    status_on_hit = status;
    blast_radius_outer = radius2;
    status_on_hit_outer = status2;
    parent_expired = false;
    children_expired = true;
}

// Main game loop calls players update which calls this update each frame
void Projectile::Update(TileMap* &tileMap) {
    // Parent has not expired
    if (!parent_expired) {
        tile_coords = sf::Vector2i(floor(sprite.getPosition().x/TILE_SIZE), floor(sprite.getPosition().y/TILE_SIZE));
        //debug_string += "(" + toString(tile_coords.x) + " " + toString(tile_coords.y) + ")";

        if (tileMap->GetTile(tile_coords.x, tile_coords.y).status == -1) { // Off screen
            parent_expired = true;
        } else if (tileMap->GetTile(tile_coords.x, tile_coords.y).status == 0) { // Hit nothing
            // Add velocity from vector field
            velocity.x += tileMap->GetTile(tile_coords.x, tile_coords.y).velocity.x;
            velocity.y += tileMap->GetTile(tile_coords.x, tile_coords.y).velocity.y;

            // Move sprite
            sprite.move(velocity.x, velocity.y);

            // Draw sprite to screen
            window.draw(sprite);
        } else { // Hit a tile
            parent_expired = true;
            Hit(tileMap);
        }
    }

    // Check for children
    if (sub_projectiles.size() > 0) {
        children_expired = false;
    } else {
        children_expired = true;
    }

    // Children have not expired
    if (!children_expired) {
        for (unsigned int i = 0; i < sub_projectiles.size(); i++) {
            sub_projectiles[i]->Update(tileMap);

            if (sub_projectiles[i]->IsExpired()) {
                delete sub_projectiles[i];
                sub_projectiles.erase(sub_projectiles.begin() + i);
            }
        }
    }

    PostUpdate(tileMap);
}

// This is called after the update function. This is mainly used by derived classed
void Projectile::PostUpdate(TileMap* &tileMap) {
    //
}

// This is called if a hit is detected
void Projectile::Hit(TileMap* &tileMap) {
    tileMap->WriteStatus(tile_coords, 0);

    for (int x = -blast_radius; x <= blast_radius; ++x) {
        for (int y = -blast_radius; y <= blast_radius; ++y) {
            sf::Vector2i p = sf::Vector2i(tile_coords.x + x, tile_coords.y + y);

            if (x*x + y*y < blast_radius*blast_radius) {
                tileMap->WriteStatus(p, status_on_hit);
            }
        }
    }

    for (int x = -blast_radius_outer; x <= blast_radius_outer; ++x) {
        for (int y = -blast_radius_outer; y <= blast_radius_outer; ++y) {
            sf::Vector2i p = sf::Vector2i(tile_coords.x + x, tile_coords.y + y);

            if (x*x + y*y < blast_radius_outer*blast_radius_outer && x*x + y*y > blast_radius*blast_radius && tileMap->GetTile(p.x, p.y).status > 0) {
                tileMap->WriteStatus(p, status_on_hit_outer);
            }
        }
    }

    PostHit(tileMap);
}

// This is called after the hit function. This is mainly used by derived classed
void Projectile::PostHit(TileMap* &tileMap) {
    //
}

// This is only used by the teleport derived class
bool Projectile::IsTeleportedInBounds(TileMap* &tileMap) {
    return false;
}

// Returns the pixel position once it's snapped to the grid
sf::Vector2f Projectile::GetPosition() {
    return sf::Vector2f(tile_coords.x * TILE_SIZE, tile_coords.y * TILE_SIZE);
}

// Returns true if this projectile has expired
bool Projectile::IsExpired() {
    return (parent_expired && children_expired);
}
