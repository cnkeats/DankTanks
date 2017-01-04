#include <math.h>
#include "Globals.h"
#include "MainMenu.h"
#include "TileMap.h"
#include "Player.h"
#include "Projectile.h"

class Application {
public:
    Application();
    ~Application();

private:
    void StartNewGame();
    void CleanUp();
    void Render();
    void UpdateMainMenu();
    void UpdateTerrain();
    void UpdatePlayers();
    void ProcessInput();
    void DrawElapsedTimeString();

    enum GameState {_MainMenuMap, _MainMenuColor, _RunningP1Turn, _RunningP2Turn, _RunningRealTime, _GameOver, _Paused};
    GameState game_state;
    GameState pre_paused_game_state;

    MainMenu *mainMenu;
    TileMap *tileMap;
    std::vector<Player*> players;
    sf::Vector2i selected_map;
    sf::Vector2i selected_p1_color;
    sf::Vector2i selected_p2_color;
    int winner_index;
    std::string elapsed_time_string;
    sf::Text text_elapsed_time;
};
