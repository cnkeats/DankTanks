#include "TileMap.h"

TileMap::~TileMap() {}

TileMap::TileMap() {
    load_state = CreatingTerrain;

    CreateTileVector();
    CreateTileMap();
}

void TileMap::Update() {
    switch (load_state) {
        case CreatingTerrain:
            CreateTerrain();
            debug_string += " [Generating] ";
            break;
        case CreatingVectorField:
            CreateVectorField();
            debug_string += " [Populating vector field] ";
            break;
        case DrawingMap:
            UpdateFallingBlocks();
            debug_string += " [Drawing Map] ";
            break;
        default:
            break;
    }
}

void TileMap::CreateTileVector() {
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
}

void TileMap::CreateTerrain() {
    // TODO Make this work for different left & right
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

    CreateTileMap();

    load_state = CreatingVectorField;
}

void TileMap::CreateVectorField() {
    //TODO Implement timer
    //TODO fix loading
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            tiles[x][y].velocity = sf::Vector2f(0.0f, -0.1f);
        }
    }

    load_state = DrawingMap;
}

void TileMap::CreateTileMap() {
    // load the tileset texture
    if (!tile_textures.loadFromFile("tile__.png"))
        return;

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(TILES_X * TILES_Y * 4);

    // populate the vertex array, with one quad per tile
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            // current tile's status
            int status = tiles[x][y].status;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(x + y * TILES_X) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
            quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(TILE_SIZE * status, 0);
            quad[1].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), 0);
            quad[2].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(TILE_SIZE * status, TILE_SIZE);
        }
    }
}

void TileMap::UpdateStatus(sf::Vector2i position, int status) {
    // current tile's status
    tiles[position.x][position.y].status = status;

    // get a pointer to the current tile's quad
    sf::Vertex* quad = &vertices[(position.x + position.y * TILES_X) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(position.x * TILE_SIZE, position.y * TILE_SIZE);
    quad[1].position = sf::Vector2f((position.x + 1) * TILE_SIZE, position.y * TILE_SIZE);
    quad[2].position = sf::Vector2f((position.x + 1) * TILE_SIZE, (position.y + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(position.x * TILE_SIZE, (position.y + 1) * TILE_SIZE);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(TILE_SIZE * status, 0);
    quad[1].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), 0);
    quad[2].texCoords = sf::Vector2f(TILE_SIZE + (TILE_SIZE * status), TILE_SIZE);
    quad[3].texCoords = sf::Vector2f(TILE_SIZE * status, TILE_SIZE);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the tileset texture
    states.texture = &tile_textures;

    // draw the vertex array
    target.draw(vertices, states);
}

void TileMap::UpdateFallingBlocks() {
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = TILES_Y - 1; y >= 0; --y) {
            if (tiles[x][y].status == 0 && tiles[x][y - 1].status == 1) {
                UpdateStatus(sf::Vector2i(x, y), 1);
                UpdateStatus(sf::Vector2i(x, y - 1), 0);
            }
        }
    }
}
