#include "Globals.h"
#include <math.h>

class Application {
public:
    Application();
    ~Application();

private:
    void InitialSetup();
    void ProcessInput();
    void Render();
    void UpdateTerrain();

    sf::RenderWindow window;
    sf::Font font;
    enum GameState {Running, Paused};
    GameState game_state;
    static const int TILE_SIZE = 20;
    static const int TERRAIN_SIZE_X = 80;
    static const int TERRAIN_SIZE_Y = 40;
    sf::RectangleShape terrain_tile;
    int terrain[TERRAIN_SIZE_Y][TERRAIN_SIZE_X];
};
