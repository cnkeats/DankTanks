#pragma once
#include "Globals.h"

struct Tile {
    int status;
    sf::Vector2f velocity;
};

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap();
    ~TileMap();
    void Update(sf::RenderWindow &);
    void UpdateStatus(sf::Vector2i, int);

    std::vector< std::vector<Tile> > tiles;

private:
    void CreateTileVector();
    void CreateTerrain();
    void CreateTileMap();
    void CreateVectorField();
    void UpdateStatus(sf::Vector2i);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static const int TILE_SIZE = 15;
    static const int TILES_X = 128;
    static const int TILES_Y = 72;
    enum LoadState {CreatingTerrain, CreatingVectorField, DrawingMap};
    LoadState load_state;
    sf::VertexArray vertices;
    sf::Texture tile_textures;
};
