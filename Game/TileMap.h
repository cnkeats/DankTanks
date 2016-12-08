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
    void Update();
    void UpdateStatus(sf::Vector2i, int);

    std::vector< std::vector<Tile> > tiles;

private:
    void CreateTileVector();
    void CreateTerrain();
    void CreateTileMap();
    void CreateVectorField();
    void UpdateFallingTiles();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    enum LoadState {CreatingTerrain, CreatingVectorField, DrawingMap};
    LoadState load_state;
    sf::VertexArray vertices;
    sf::Texture tile_textures;
};
