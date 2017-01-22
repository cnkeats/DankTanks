#include <math.h>
#include "Globals.h"
#include "GameStartingInfo.h"
#include "MainMenu.h"
#include "TileMap.h"
#include "Player.h"
#include "Projectile.h"

class Application {
public:
    Application();
    ~Application();

private:
    void StartNewMenu();
    void StartNewGame();
    void CleanUp();
    void Render();
    void UpdateMainMenu();
    void UpdateTerrain();
    void UpdatePlayers();
    void ProcessInput();
    void DrawElapsedTimeString();

    enum GameState {_MainMenu, _Running, _GameOver, _Paused};
    GameState game_state;
    GameState pre_paused_game_state;

    MainMenu *main_menu;
    TileMap *tile_map;
    std::vector<Player*> players;
    std::string elapsed_time_string;
    sf::Text text_elapsed_time;
    sf::Clock game_clock;
    sf::Clock game_budget_clock;
    GameStartingInfo game_starter;

    bool is_turn_based;
    int winner_index;
};
