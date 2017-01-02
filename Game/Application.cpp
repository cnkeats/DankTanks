#include "Application.h"

Application::~Application() {
    CleanUp();
}

// Main game loop
Application::Application() {
    window.create(sf::VideoMode(1, 1), "Dank Tanks!", sf::Style::Fullscreen); // Create window
    window.setMouseCursorVisible(false);

    font.loadFromFile("Cousine-Regular.ttf"); // Load a font for sf::Text

    StartNewGame();

    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); // Use a fixed time step, 60 fps
    sf::Clock clock;
    sf::Time elapsed_time;

    // Main game loop
    while (window.isOpen()) {
        elapsed_time = clock.restart();
        elapsed_time_string = ToString(elapsed_time.asMicroseconds()) + " / 16666 ";
        debug_string = "";

        while (elapsed_time < TIME_PER_FRAME) {
            ProcessInput();
            elapsed_time += clock.restart();
        }

        Render();
    }
}

// Creates a menu and 2 players
void Application::StartNewGame() {
    game_state = _MainMenuMap; // Initialize game state

    mainMenu = new MainMenu(); // Create menu

    // Create players
    players.push_back(new Player(sf::Vector2f(5 * TILE_SIZE, 0), 0));
    players.push_back(new Player(sf::Vector2f((TILES_X - 5) * TILE_SIZE, 0), 1));

    selected_p1_color = sf::Vector2i(-1, -1);
    selected_p2_color = sf::Vector2i(-1, -1);

    winner = -1;

    text_elapsed_time.setFont(font);
    text_elapsed_time.setCharacterSize(20);
    text_elapsed_time.setColor(sf::Color::White);
    text_elapsed_time.setPosition(window.getSize().x - 180, 0);
}

// Deletes
void Application::CleanUp() {
    delete tileMap;

    delete mainMenu;

    for (unsigned int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    players.clear();
}

// Render based on game state
void Application::Render() {
    switch (game_state) {
        case _MainMenuMap:
            window.clear(sf::Color(sf::Color(69, 69, 69, 255)));
            UpdateMainMenu();
            break;
        case _MainMenuColor:
            window.clear(sf::Color(sf::Color(69, 69, 69, 255)));
            UpdateMainMenu();
            break;
        case _RunningP1Turn:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            break;
        case _RunningP2Turn:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            break;
        case _RunningRealTime:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            break;
        case _GameOver:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            if (winner == 0) {
                debug_string = "Game Over! The game was a draw! Press fire to start a new game!";
            } else {
                debug_string = "Game Over! Player " + ToString(winner) + " won! Press fire to start a new game!";
            }
            break;
        case _Paused:
            break;
        default:
            debug_string = "Game state error";
            break;
    }

    if (game_state != _Paused) {
        DrawDebugString();
        DrawElapsedTimeString();
    }

    window.display();
}

// Update main menu which includes map and player color selection
void Application::UpdateMainMenu() {
    mainMenu->Update();
    window.draw(*mainMenu);
}

// Update terrain using 2D array and tiles
void Application::UpdateTerrain() {
    tileMap->Update();
    window.draw(*tileMap);
}

// Update all players
void Application::UpdatePlayers() {
    for (unsigned int i = 0; i < players.size(); ++i) {
        players[i]->Update(tileMap);
    }

    if (game_state != _GameOver) {
        if (players[0]->IsDead() && players[1]->IsDead()) {
            winner = 0;
            game_state = _GameOver;
        } else if (players[0]->IsDead()) {
            winner = 2;
            game_state = _GameOver;
        } else if (players[1]->IsDead()) {
            winner = 1;
            game_state = _GameOver;
        }
    }
}

// Handle user input
void Application::ProcessInput() {
    if (game_state == _MainMenuColor && selected_p1_color != sf::Vector2i(-1, -1) && selected_p2_color != sf::Vector2i(-1, -1)) {
        game_state = _RunningRealTime;
        //game_state = _RunningP1Turn;
    } else if (game_state == _RunningP1Turn && players[0]->IsTurnOver()) {
        game_state = _RunningP2Turn;
    } else if (game_state == _RunningP2Turn && players[1]->IsTurnOver()) {
        game_state = _RunningP1Turn;
    }

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // Close window
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { // Pause
                if (game_state != _Paused) {
                    pre_paused_game_state = game_state;
                    game_state = _Paused;
                } else {
                    game_state = pre_paused_game_state;
                }

            // Player 1 controls
            } else if (event.key.code == sf::Keyboard::Space) { // Fire
                if (game_state == _MainMenuMap) {
                    selected_map = mainMenu->InputP1Select();
                    tileMap = new TileMap(selected_map);
                    game_state = _MainMenuColor;
                } else if (game_state == _MainMenuColor) {
                    selected_p1_color = mainMenu->InputP1Select();
                    players[0]->SetColor(selected_p1_color);
                } else if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputFire();
                } else if (game_state == _GameOver) {
                    CleanUp();
                    StartNewGame();
                }
            } else if (event.key.code == sf::Keyboard::Up) { // Up
                if (game_state == _MainMenuMap || game_state == _MainMenuColor) {
                    mainMenu->InputP1Up();
                } else if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputRotateClockwise();
                }
            } else if (event.key.code == sf::Keyboard::Down) { // Down
                if (game_state == _MainMenuMap || game_state == _MainMenuColor) {
                    mainMenu->InputP1Down();
                } else if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputRotateCounterClockwise();
                }
            } else if (event.key.code == sf::Keyboard::Left) { // Left
                if (game_state == _MainMenuMap || game_state == _MainMenuColor) {
                    mainMenu->InputP1Left();
                } else if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputMoveLeft(tileMap);
                }
            } else if (event.key.code == sf::Keyboard::Right) { // Right
                if (game_state == _MainMenuMap || game_state == _MainMenuColor) {
                    mainMenu->InputP1Right();
                } else if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputMoveRight(tileMap);
                }
            } else if (event.key.code == sf::Keyboard::RShift) { // Change projectile
                if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputCycleProjectileType();
                }
            } else if (event.key.code == sf::Keyboard::Equal) { // Increase power
                if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputPowerUp();
                }
            } else if (event.key.code == sf::Keyboard::Dash) { // Decrease power
                if (game_state == _RunningP1Turn || game_state == _RunningRealTime) {
                    players[0]->InputPowerDown();
                }

            // Player 2 controls
            } else if (event.key.code == sf::Keyboard::Return) { // Fire
                if (game_state == _MainMenuMap) {
                    selected_map = mainMenu->InputP1Select();
                    tileMap = new TileMap(selected_map);
                    game_state = _MainMenuColor;
                } else if (game_state == _MainMenuColor) {
                    selected_p2_color = mainMenu->InputP2Select();
                    players[1]->SetColor(selected_p2_color);
                } else if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputFire();
                } else if (game_state == _GameOver) {
                    CleanUp();
                    StartNewGame();
                }
            } else if (event.key.code == sf::Keyboard::Numpad8) { // Up
                if (game_state == _MainMenuMap) {
                    mainMenu->InputP1Up();
                } else if (game_state == _MainMenuColor) {
                    mainMenu->InputP2Up();
                } else if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputRotateClockwise();
                }
            } else if (event.key.code == sf::Keyboard::Numpad5) { // Down
                if (game_state == _MainMenuMap) {
                    mainMenu->InputP1Down();
                } else if (game_state == _MainMenuColor) {
                    mainMenu->InputP2Down();
                } else if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputRotateCounterClockwise();
                }
            } else if (event.key.code == sf::Keyboard::Numpad4) { // Left
                if (game_state == _MainMenuMap) {
                    mainMenu->InputP1Left();
                } else if (game_state == _MainMenuColor) {
                    mainMenu->InputP2Left();
                } else if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputMoveLeft(tileMap);
                }
            } else if (event.key.code == sf::Keyboard::Numpad6) { // Right
                if (game_state == _MainMenuMap) {
                    mainMenu->InputP1Right();
                } else if (game_state == _MainMenuColor) {
                    mainMenu->InputP2Right();
                } else if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputMoveRight(tileMap);
                }
            } else if (event.key.code == sf::Keyboard::Numpad7) { // Change projectile
                if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputCycleProjectileType();
                }
            } else if (event.key.code == sf::Keyboard::Numpad2) { // Increase power
                if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputPowerUp();
                }
            } else if (event.key.code == sf::Keyboard::Numpad0) { // Decrease power
                if (game_state == _RunningP2Turn || game_state == _RunningRealTime) {
                    players[1]->InputPowerDown();
                }
            }
        }
    }
}

void Application::DrawElapsedTimeString() {
    text_elapsed_time.setString(elapsed_time_string);
    window.draw(text_elapsed_time);
}
