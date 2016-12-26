#include "TileMap.h"

TileMap::~TileMap() {}

TileMap::TileMap(sf::Vector2i selected) {
    load_state = _GeneratingTerrain;
    selected_map = selected;
}

// Main game loop calls this update function
void TileMap::Update() {
    switch (load_state) {
        case _GeneratingTerrain:
            GenerateTerrain();
            //debug_string += " [Generating] ";
            break;
        case _PopulatingVectorField:
            PopulateVectorField();
            //debug_string += " [Populating vector field] ";
            break;
        case _UpdatingMap:
            UpdateFallingTiles();
            //debug_string += " [Drawing Map] ";
            break;
        default:
            break;
    }
}

// Create terrain but updating statuses to 1 based on an equation
void TileMap::GenerateTerrain() {
    // Create 2D vector for tile map
    std::vector<Tile> temp_column;
    Tile temp_tile;
    temp_tile.status = 0;
    temp_tile.velocity = sf::Vector2f(0.0f, 0.0f);

    for (int x = 0; x < TILES_X; ++x) {
        tiles.push_back(temp_column);

        for (int y = 0; y < TILES_Y; ++y) {
            tiles[x].push_back(temp_tile);
        }
    }

    if (selected_map == sf::Vector2i(0, 0)) {
        // Use math to generate terrain
        int x = 0;
        int sign = -1;
        int number_of_peaks_and_valleys = 6;
        float amplitude = 1;

        while (x < TILES_X) {
            if (sign > 0) {
                amplitude = rand()%(TILES_Y * 1/5) + 5;
            } else {
                amplitude = rand()%(TILES_Y * 2/3) + 8;
            }

            for (float x_f = 0; x_f < PI; x_f += PI / (TILES_X / number_of_peaks_and_valleys)) {
                float fx_f = sign * amplitude * sin(x_f) + TILES_Y * 0.75;

                int fx = static_cast<int> (fx_f);

                if (fx < 0) {
                    fx = 0;
                }

                if (fx < TILES_Y) {
                    tiles[x][fx].status = 1;

                    for (int y = TILES_Y - 1; y > fx; --y) {
                        tiles[x][y].status = 1;
                    }
                }
                ++x;

                if (x >= TILES_X) {
                    break;
                }
            }
            sign *= -1;
        }
    } else if (selected_map == sf::Vector2i(1, 0)) {
        for (int x = 0; x < TILES_X; ++x) {
            for (int y = 0; y < TILES_Y; ++y) {
                if (y > TILES_Y - 30) {
                    tiles[x][y].status = 2;
                }
            }
        }
    } else if (selected_map == sf::Vector2i(2, 0)) {
        // TODO Make this work better for different left & right for varied terrain
        // TODO It's f(x) = 100*(x-100)(x-50)(x-0)(x+50)... currently
        int left = -2;
        int right = 5;

        for (int x = 0; x < TILES_X; ++x) {
            float fx_f = 100;
            for (int i = left; i < right; ++i) {
                fx_f *= (x - i*50);
             }

            for (int i = left; i < right; ++i) {
                fx_f /= 100;
            }

            fx_f += 80;
            int fx = static_cast<int> (fx_f);

            if (fx >= 0 && fx < TILES_Y) {
                tiles[x][fx].status = 1;

                for (int y = TILES_Y - 1; y > fx; --y) {
                    tiles[x][y].status = 1;
                }
            }
        }
    } else if (selected_map == sf::Vector2i(3, 0)) {
        // Use math to generate terrain
        int x = 0;
        int sign = -1;
        int number_of_peaks_and_valleys = 6;
        int inner_coefficient = 4;
        float amplitude = 1;
        float amplitude2 = 1;

        while (x < TILES_X) {
            if (sign > 0) {
                amplitude = rand()%(TILES_Y * 1/7) + 5;
                amplitude2 = rand()%(TILES_Y * 1/20) + 1;
            } else {
                amplitude = rand()%(TILES_Y * 1/2) + 8;
                amplitude2 = rand()%(TILES_Y * 1/10) + 1;
            }

            for (float x_f = 0; x_f < PI; x_f += PI / (TILES_X / number_of_peaks_and_valleys)) {
                float fx_f = sign * amplitude * sin(x_f) + TILES_Y * 0.75;
                fx_f -= sign * amplitude2 * sin(inner_coefficient * x_f) + TILES_Y * 0.1;

                int fx = static_cast<int> (fx_f);

                if (fx < 0) {
                    fx = 0;
                }

                if (fx < TILES_Y) {
                    tiles[x][fx].status = 1;

                    for (int y = TILES_Y - 1; y > fx; --y) {
                        tiles[x][y].status = 1;
                    }
                }
                ++x;

                if (x >= TILES_X) {
                    break;
                }
            }
            sign *= -1;
        }
    } else if (selected_map == sf::Vector2i(0, 1)) {
        for (int x = 0; x < TILES_X; ++x) {
            for (int y = 0; y < TILES_Y; ++y) {
                if (x == y || x == -1 * y + TILES_X - 1 || (x >= TILES_Y && y == TILES_Y - 1)) {
                    tiles[x][y].status = 1;

                    for (int y_fill = TILES_Y - 1; y_fill > y; --y_fill) {
                        tiles[x][y_fill].status = 1;
                    }
                }
            }
        }
    } else if (selected_map == sf::Vector2i(1, 1)) {
        // Use math to generate terrain
        int x = 0;
        int sign = -1;
        int number_of_peaks_and_valleys = 8;
        float amplitude = 1;

        while (x < TILES_X) {
            if (sign > 0) {
                amplitude = rand()%(TILES_Y * 1/5) + 5;
            } else {
                amplitude = rand()%(TILES_Y * 2/3) + 8;
            }

            for (float x_f = 0; x_f < PI; x_f += PI / (TILES_X / number_of_peaks_and_valleys)) {
                float fx_f = sign * amplitude + TILES_Y * 0.75;

                int fx = static_cast<int> (fx_f);

                if (fx < 0) {
                    fx = 0;
                }

                if (fx < TILES_Y) {
                    tiles[x][fx].status = 1;

                    for (int y = TILES_Y - 1; y > fx; --y) {
                        tiles[x][y].status = 1;
                    }
                }
                ++x;

                if (x >= TILES_X) {
                    break;
                }
            }
            sign *= -1;
        }
    } else if (selected_map == sf::Vector2i(2, 1)) {
        // Use math to generate terrain
        int x = 0;
        int sign = -1;
        int number_of_peaks_and_valleys = 6;
        float amplitude = 1;

        while (x < TILES_X) {
            amplitude = rand()%(TILES_Y * 2/3) + 8;

            for (float x_f = 0; x_f < PI; x_f += PI / (TILES_X / number_of_peaks_and_valleys)) {
                float fx_f = sign * amplitude * sin(x_f) + TILES_Y * 0.75;

                int fx = static_cast<int> (fx_f);

                if (fx < 0) {
                    fx = 0;
                }

                if (fx < TILES_Y) {
                    tiles[x][fx].status = 1;

                    for (int y = TILES_Y - 1; y > fx; --y) {
                        tiles[x][y].status = 1;
                    }
                }
                ++x;

                if (x >= TILES_X) {
                    break;
                }
            }
        }
    } else if (selected_map == sf::Vector2i(3, 1)) {
        // Use math to generate terrain
        int x = 0;
        int sign = 1;
        int number_of_peaks_and_valleys = 6;
        float amplitude = 1;

        while (x < TILES_X) {
            amplitude = rand()%(TILES_Y * 2/3) + 8;

            for (float x_f = 0; x_f < PI; x_f += PI / (TILES_X / number_of_peaks_and_valleys)) {
                float fx_f = sign * amplitude * sin(x_f) + TILES_Y * 0.25;

                int fx = static_cast<int> (fx_f);

                if (fx < 0) {
                    fx = 0;
                }

                if (fx < TILES_Y) {
                    tiles[x][fx].status = 1;

                    for (int y = TILES_Y - 1; y > fx; --y) {
                        tiles[x][y].status = 1;
                    }
                }
                ++x;

                if (x >= TILES_X) {
                    break;
                }
            }
        }
    } else {
        // border 1
        for (int x = 0; x < TILES_X; ++x) {
            for (int y = 0; y < TILES_Y; ++y) {
                if (x == 0 || x == TILES_X - 1 || y == 0 || y == TILES_Y - 1) {
                    tiles[x][y].status = 2;
                }
            }
        }
    }

    // border 1
    /*for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            if (x == 0 || x == TILES_X - 1 || y == 0 || y == TILES_Y - 1) {
                tiles[x][y].status = 2;
            }
        }
    }*/
    // border 2
    /*for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            if (x == 0 || x == 1 || x == TILES_X - 1 || x == TILES_X - 2 ||
                y == 0 || y == 1 || y == TILES_Y - 1 || y == TILES_Y - 2) {
                tiles[x][y].status = 2;
            }
        }
    }*/

    MakeTerrainDrawable();
    load_state = _PopulatingVectorField;
}

// Populate vector field for each tile.
void TileMap::PopulateVectorField() {
    //TODO Implement timer for complex gravity calculated over several frames
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            tiles[x][y].velocity = sf::Vector2f(0.0f, 0.16f);
        }
    }

    load_state = _UpdatingMap;
}

// Create actual drawable map using a vertex array
void TileMap::MakeTerrainDrawable() {
    // load the tileset texture
    if (!tile_textures.loadFromFile(TILE_FILE)) {
        //TODO
    }

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::TrianglesStrip);
    vertices.resize(TILES_X * TILES_Y * 7);

    // populate the vertex array, with one quad per tile
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            WriteStatus(x, y, tiles[x][y].status);
        }
    }
}

// Redefine each tile's texture based on its status each frame
void TileMap::WriteStatus(sf::Vector2i position, int status) {
    if (!IsInBounds(position)) {
        return;
    }

    int x = position.x;
    int y = position.y;

    // Pass -1 to leave the tile unaffected
    if (status >= 0) {
        // current tile's status
        tiles[x][y].status = status;

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &vertices[(x + y * TILES_X) * 7];

        // define its 4 corners
        quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        quad[1].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
        quad[3].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
        quad[4].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);
        quad[5].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        quad[6].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);

        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(TILE_SIZE * status, 0);
        quad[1].texCoords = sf::Vector2f(TILE_SIZE * status, 0);
        quad[2].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), 0);
        quad[3].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), TILE_SIZE);
        quad[4].texCoords = sf::Vector2f(TILE_SIZE * status, TILE_SIZE);
        quad[5].texCoords = sf::Vector2f(TILE_SIZE * status, 0);
        quad[6].texCoords = sf::Vector2f(TILE_SIZE * status, TILE_SIZE);
    }
}

// Redefine each tile's texture based on its status each frame
void TileMap::WriteStatus(int x, int y, int status) {
    WriteStatus(sf::Vector2i(x, y), status);
}

// Read the status of a tile at a position. Returns (-1, (-1, -1)) if out of bounds
Tile TileMap::GetTile(sf::Vector2i position) {
    if (IsInBounds(position)) {
        return tiles[position.x][position.y];
    } else {
        Tile t;
        t.status = -1;
        t.velocity = sf::Vector2f(0, 0);
        return t;
    }
}

// Read the status of a tile at a position
Tile TileMap::GetTile(int x, int y) {
    return GetTile(sf::Vector2i(x, y));
}

// Virtual draw
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the tileset texture
    states.texture = &tile_textures;

    // draw the vertex array
    target.draw(vertices, states);
}

// Move each tile down 1 tile per frame if space exists below it
void TileMap::UpdateFallingTiles() {
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = TILES_Y - 1; y >= 0; --y) {
            if (tiles[x][y].status == 0 && tiles[x][y - 1].status == 1) {
                WriteStatus(sf::Vector2i(x, y), 1);
                WriteStatus(sf::Vector2i(x, y - 1), 0);
            }
        }
    }
}

// Returns true if this xy coordinate is in the tile map's range
bool TileMap::IsInBounds(sf::Vector2i v) {
    return v.x >= 0 && v.x < TILES_X && v.y >= 0 && v.y < TILES_Y;
}

// Returns true if this xy coordinate is in the tile map's range
bool TileMap::IsInBounds(sf::Vector2f v) {
    return v.x >= 0 && v.x < TILES_X * TILE_SIZE && v.y >= 0 && v.y < TILES_Y * TILE_SIZE;
}

