#pragma once
#include "Globals.h"

struct Tile {
    int status;
    sf::Vector2f velocity;
};

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap(sf::Vector2i);
    ~TileMap();
    void Update();
    void UpdateStatus(sf::Vector2i, int);

    std::vector< std::vector<Tile> > tiles;

private:
    void GenerateTerrain();
    void MakeTerrainDrawable();
    void PopulateVectorField();
    void UpdateFallingTiles();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    enum LoadState {_GeneratingTerrain, _PopulatingVectorField, _UpdatingMap};
    LoadState load_state;

    sf::VertexArray vertices;
    sf::Texture tile_textures;
    sf::Vector2i selected_map;
};
