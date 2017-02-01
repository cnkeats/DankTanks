#pragma once
#include "Globals.h"

class TileMap : public sf::Drawable {
public:
    TileMap(int);
    ~TileMap();
    void Update();
    void WriteStatus(int, int, int);
    void WriteStatus(sf::Vector2i, int);
    Tile GetTile(int, int);
    Tile GetTile(sf::Vector2i);

private:
    void GenerateTerrain();
    void MakeTerrainDrawable();
    void PopulateVectorField();
    void UpdateFallingTiles();
    void WriteStatus(sf::Vector2i, int, bool);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    bool IsInBounds(sf::Vector2i);
    bool IsInBounds(sf::Vector2f);

    enum LoadState {_GeneratingTerrain, _PopulatingVectorField, _UpdatingMap};
    LoadState load_state;

    std::vector< std::vector<Tile> > tiles;
    sf::VertexArray vertices;
    sf::Texture tile_textures;
    int selected_map;
};
