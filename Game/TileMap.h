#pragma once
#include "Globals.h"

class TileMap : public sf::Drawable {
public:
    TileMap(sf::Vector2i);
    ~TileMap();
    void Update();
    void WriteStatus(sf::Vector2i, int);
    void WriteStatus(int, int, int);
    Tile GetTile(sf::Vector2i);
    Tile GetTile(int, int);

private:
    void GenerateTerrain();
    void MakeTerrainDrawable();
    void PopulateVectorField();
    void UpdateFallingTiles();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    bool IsInBounds(sf::Vector2i);
    bool IsInBounds(sf::Vector2f);

    enum LoadState {_GeneratingTerrain, _PopulatingVectorField, _UpdatingMap};
    LoadState load_state;

    std::vector< std::vector<Tile> > tiles;
    sf::VertexArray vertices;
    sf::Texture tile_textures;
    sf::Vector2i selected_map;
};
