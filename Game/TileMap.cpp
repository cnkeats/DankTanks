#include "TileMap.h"

TileMap::~TileMap() {}

TileMap::TileMap() {
    load_state = GeneratingBodies;
    bodies_to_generate = 30;

    PopulateTileTypes();
    PopulateTiles();
}

void TileMap::Update(sf::RenderWindow &window) {
    switch (load_state) {
        case GeneratingBodies:
            Generate();
            debug_string += " [Generating bodies]";
            break;
        case PopulatingVectorField:
            PopulateVectorField();
            debug_string += " [Populating vector field]";
            break;
        case DrawingMap:
            DrawMap(window);
            debug_string += " [Drawing Map]";
            break;
        default:
            break;
    }
}

void TileMap::PopulateTileTypes() {
    // 0
    sf::RectangleShape temp_tile;
    temp_tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    temp_tile.setOutlineColor(sf::Color(127, 127, 127, 255));
    temp_tile.setOutlineThickness(1);
    tile_types.push_back(temp_tile);

    // 1
    temp_tile.setFillColor(sf::Color::Black);
    tile_types.push_back(temp_tile);

    // 2
    temp_tile.setFillColor(sf::Color::Red);
    tile_types.push_back(temp_tile);
}

void TileMap::PopulateTiles() {
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

void TileMap::Generate() {
    if (bodies_to_generate > 0) {
        GenerateBody();
        bodies_to_generate--;
    } else {
        load_state = PopulatingVectorField;
    }
}

void TileMap::GenerateBody() {
    //TODO Implement timer
    sf::Vector2i center = sf::Vector2i(rand()%TILES_X, rand()%TILES_Y);

    for (int x = -4; x < 5; ++x) {
        for (int y = -4; y < 5; ++y) {
            if (abs(x) + abs(y) <= 6 && center.x + x >= 0 && center.x + x < TILES_X && center.y + y >= 0 && center.y + y < TILES_Y) {
                tiles[center.x + x][center.y + y].status = 1;
            }
        }
    }
}

void TileMap::PopulateVectorField() {
    //TODO Implement timer
    //TODO fix loading
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            if (tiles[x][y].status == 0) {
                tiles[x][y].velocity = sf::Vector2f(0.0f, -0.1f);
            } else if (tiles[x][y].status == 1) {
                tiles[x][y].velocity = sf::Vector2f(0.0f, 0.0f);
            }
        }
    }

    load_state = DrawingMap;
}

void TileMap::DrawMap(sf::RenderWindow &window) {
    for (int x = 0; x < TILES_X; ++x) {
        for (int y = 0; y < TILES_Y; ++y) {
            if (tiles[x][y].status > 0) {
                tile_types[tiles[x][y].status].setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(tile_types[tiles[x][y].status]);
            }
        }
    }
}
