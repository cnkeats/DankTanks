#include "Projectile.h"

Projectile::~Projectile() {
    for (unsigned int i = 0; i < sub_projectiles.size(); i++) {
        delete sub_projectiles[i];
    }
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f angle) {
    position = p;
    velocity = angle;
    blast_radius = 5.1;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;

    PopulateVertexArray();
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f angle, float radius, int status) {
    position = p;
    velocity = angle;
    blast_radius = radius;
    status_on_hit = status;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;

    PopulateVertexArray();
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f angle, float radius, int status, float radius2, int status2) {
    position = p;
    velocity = angle;
    blast_radius = radius;
    status_on_hit = status;
    blast_radius_outer = radius2;
    status_on_hit_outer = status2;
    parent_expired = false;
    children_expired = true;

    PopulateVertexArray();
}

// Populate vertex array for drawing
void Projectile::PopulateVertexArray() {
    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::Points);
    vertices.resize(4);

    sf::Vertex* v = &vertices[0];

    v[0].position = sf::Vector2f(position.x, position.y);
    v[1].position = sf::Vector2f(position.x + 1, position.y);
    v[2].position = sf::Vector2f(position.x + 1, position.y + 1);
    v[3].position = sf::Vector2f(position.x, position.y + 1);

    v[0].color = sf::Color::Cyan;
    v[1].color = sf::Color::Cyan;
    v[2].color = sf::Color::Cyan;
    v[3].color = sf::Color::Cyan;
}

// Main game loop calls players update which calls this update each frame
void Projectile::Update(TileMap* &tileMap) {
    // Parent has not expired
    if (!parent_expired) {
        sf::Vertex* v = &vertices[0];
        position = v[0].position;

        tile_coords = sf::Vector2i(floor(position.x / TILE_SIZE), floor(position.y / TILE_SIZE));

        if (tileMap->GetTile(tile_coords.x, tile_coords.y).status == -1) { // Off screen
            parent_expired = true;
        } else if (tileMap->GetTile(tile_coords.x, tile_coords.y).status == 0) { // Hit nothing
            // Add velocity from vector field
            velocity.x += tileMap->GetTile(tile_coords.x, tile_coords.y).velocity.x;
            velocity.y += tileMap->GetTile(tile_coords.x, tile_coords.y).velocity.y;

            // Move sprite
            position = sf::Vector2f(position.x + velocity.x, position.y + velocity.y);

            // get a pointer to the current tile's tile
            sf::Vertex* v = &vertices[0];

            // define its 4 corners
            v[0].position = sf::Vector2f(position.x, position.y);
            v[1].position = sf::Vector2f(position.x + 1, position.y);
            v[2].position = sf::Vector2f(position.x + 1, position.y + 1);
            v[3].position = sf::Vector2f(position.x, position.y + 1);
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
            window.draw(*sub_projectiles[i]);

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
    tileMap->WriteStatus(tile_coords, status_on_hit);

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

// Virtual draw
void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!parent_expired) {
        // draw the vertex array
        target.draw(vertices, states);
    }
}
