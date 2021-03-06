#include "Projectile.h"
#include "Player.h"

Projectile::~Projectile() {
    for (unsigned int i = 0; i < sub_projectiles.size(); i++) {
        delete sub_projectiles[i];
    }
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f v) {
    position = p;
    velocity = v;
    blast_radius = 3.2;
    status_on_hit = 0;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;
    starting_life_ticks = 360;
    life_ticks = starting_life_ticks;
    damage = 10;

    PopulateVertexArray();
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f v, float r, int s, int d) {
    position = p;
    velocity = v;
    blast_radius = r;
    status_on_hit = s;
    damage = d;
    blast_radius_outer = 0;
    status_on_hit_outer = 0;
    parent_expired = false;
    children_expired = true;
    starting_life_ticks = 360;
    life_ticks = starting_life_ticks;

    PopulateVertexArray();
}

Projectile::Projectile(sf::Vector2f p, sf::Vector2f v, float r, int s, int d, float r2, int s2) {
    position = p;
    velocity = v;
    blast_radius = r;
    status_on_hit = s;
    damage = d;
    blast_radius_outer = r2;
    status_on_hit_outer = s2;
    parent_expired = false;
    children_expired = true;
    starting_life_ticks = 360;
    life_ticks = starting_life_ticks;

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
void Projectile::Update(TileMap* &tile_map, std::vector<Player*> &players, int owner_index, std::vector<Explosion*> &explosions) {
    // Parent has not expired
    if (!parent_expired) {
        sf::Vertex* v = &vertices[0];
        position = v[0].position;

        tile_coords = sf::Vector2i(floor(position.x / TILE_SIZE), floor(position.y / TILE_SIZE));

        if (tile_map->GetTile(tile_coords.x, tile_coords.y).status == -1) { // Off screen
            parent_expired = true;
        } else {
            if (tile_map->GetTile(tile_coords.x, tile_coords.y).status == 0 && !PlayerWasHit(players, owner_index)) { // Hit nothing
                // Add velocity from vector field
                velocity.x += tile_map->GetTile(tile_coords.x, tile_coords.y).velocity.x;
                velocity.y += tile_map->GetTile(tile_coords.x, tile_coords.y).velocity.y;

                // Move sprite
                position = sf::Vector2f(position.x + velocity.x, position.y + velocity.y);

                // Get a pointer to the current projectile's top left
                sf::Vertex* v = &vertices[0];

                // Define its 4 corners
                v[0].position = sf::Vector2f(position.x, position.y);
                v[1].position = sf::Vector2f(position.x + 1, position.y);
                v[2].position = sf::Vector2f(position.x + 1, position.y + 1);
                v[3].position = sf::Vector2f(position.x, position.y + 1);
            } else { // Hit a tile or player
                parent_expired = true;
                Hit(tile_map, players, owner_index, explosions);
            }
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
            sub_projectiles[i]->Update(tile_map, players, owner_index, explosions);
            window.draw(*sub_projectiles[i]);

            if (sub_projectiles[i]->IsExpired()) {
                delete sub_projectiles[i];
                sub_projectiles.erase(sub_projectiles.begin() + i);
            }
        }
    }

    --life_ticks;

    PostUpdate(tile_map, players, owner_index, explosions);
}

// This is called after the update function. This is mainly used by derived classed
void Projectile::PostUpdate(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    //
}

// This is called if a hit is detected
void Projectile::Hit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    // Blast radius, deals damage
    for (int y = -blast_radius; y <= blast_radius; ++y) {
        for (int x = -blast_radius; x <= blast_radius; ++x) {
            sf::Vector2i p = sf::Vector2i(tile_coords.x + x, tile_coords.y + y);

            if (x*x + y*y < blast_radius*blast_radius) {
                tile_map->WriteStatus(p, status_on_hit);

                for (unsigned int i = 0; i < players.size(); ++i) {
                    if (players[i]->IsOnTile(p)) { // Player is on this tile
                        int dmg = damage - floor(abs(x) + abs(y)); // damage - xy offset
                        if (dmg > 0) {
                            players[i]->UpdateHitPoints(dmg);
                        } else {
                            players[i]->UpdateHitPoints(1);
                        }
                    }
                }
            }
        }
    }

    // Outer radius, doesn't deal damage
    if (blast_radius_outer > 0) {
        for (int x = -blast_radius_outer; x <= blast_radius_outer; ++x) {
            for (int y = -blast_radius_outer; y <= blast_radius_outer; ++y) {
                sf::Vector2i p = sf::Vector2i(tile_coords.x + x, tile_coords.y + y);

                if (x*x + y*y < blast_radius_outer*blast_radius_outer && x*x + y*y > blast_radius*blast_radius && tile_map->GetTile(p.x, p.y).status > 0) {
                    tile_map->WriteStatus(p, status_on_hit_outer);
                }
            }
        }
    }

    explosions.push_back(new Explosion(position, blast_radius));

    PostHit(tile_map, players, owner_index, explosions);
}

// This is called after the hit function. This is mainly used by derived classed
void Projectile::PostHit(TileMap* &tile_map, std::vector<Player*> &players, unsigned int owner_index, std::vector<Explosion*> &explosions) {
    //
}

bool Projectile::PlayerWasHit(std::vector<Player*> &players, unsigned int owner_index) {
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->IsOnTile(tile_coords)) { // Hit a player
            if (i == owner_index && life_ticks > starting_life_ticks - 5) { // don't hit yourself for first 5 frames
                return false;
            } else if (life_ticks > starting_life_ticks - 1) { // direct hit bug otherwise if projectile spawns children
                return false;
            } else {
                return true;
            }
        }
    }

    return false;
}

// Returns true if this projectile has expired
bool Projectile::IsExpired() {
    return ((parent_expired && children_expired) || life_ticks <= 0);
}

// Virtual draw
void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!parent_expired) {
        // draw the vertex array
        target.draw(vertices, states);
    }
}
