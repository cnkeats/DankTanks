#include <math.h>
#include "Globals.h"
#include "TileMap.h"
#include "Player.h"
#include "Projectile.h"

class Application {
public:
    Application();
    ~Application();

private:
    void InitialSetup();
    void ProcessInput();
    void Render();
    void UpdateTerrain();
    void UpdatePlayers();

    sf::RenderWindow window;
    sf::Font font;
    enum GameState {Running, Paused};
    GameState game_state;

    TileMap *tileMap;
    std::vector<Player*> players;
};
