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
    game_state = _MainMenu; // Initialize game state

    main_menu = new MainMenu(); // Create menu

    is_turn_based = false;

    selected_map = -1;
    selected_p1_class = -1;
    selected_p2_class = -1;

    winner_index = -2;

    text_elapsed_time.setFont(font);
    text_elapsed_time.setCharacterSize(20);
    text_elapsed_time.setColor(sf::Color::White);
    text_elapsed_time.setPosition(window.getSize().x - 180, 0);
}

// Render based on game state
void Application::Render() {
    switch (game_state) {
        case _MainMenu:
            window.clear(sf::Color(sf::Color(69, 69, 69, 255)));
            UpdateMainMenu();
            break;
        case _Running:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            break;
        case _GameOver:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            if (winner_index == -1) {
                debug_string = "Game Over! The game was a draw! Press fire to start a new game!";
            } else {
                debug_string = "Game Over! Player " + ToString(winner_index + 1) + " won! Press fire to start a new game!";
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
    main_menu->Update();
    window.draw(*main_menu);

    if (game_state == _MainMenu && selected_map != -1) {
        game_state = _Running;

        // Create players
        players.push_back(new Player(0, is_turn_based, selected_p1_class, sf::Vector2f(8 * TILE_SIZE, 0)));
        players.push_back(new Player(1, is_turn_based, selected_p2_class, sf::Vector2f((TILES_X - 10) * TILE_SIZE, 0)));

        players[0]->SetActive();
        game_clock.restart();
        game_budget_clock.restart();
    }
}

// Update terrain using 2D array and tiles
void Application::UpdateTerrain() {
    tile_map->Update();
    window.draw(*tile_map);
}

// Update all players
void Application::UpdatePlayers() {
    debug_string += "Game Clock: " + ToString(game_clock.getElapsedTime().asSeconds()) + "\n" + ToString(game_budget_clock.getElapsedTime().asSeconds());

    // In real time mode, every 5 seconds add budget
    if (!is_turn_based && game_budget_clock.getElapsedTime().asSeconds() >= 5) {
        game_budget_clock.restart();

        for (unsigned int i = 0; i < players.size(); ++i) {
            players[i]->AddBudget();
        }
    }

    // In real time mode, after 60 seconds enter overtime
    if (!is_turn_based && game_clock.getElapsedTime().asSeconds() >= 60) {
        for (unsigned int i = 0; i < players.size(); ++i) {
            players[i]->SetOvertime();
        }
    }

    // Update all players
    for (unsigned int i = 0; i < players.size(); ++i) {
        players[i]->Update(tile_map, players);
    }

    // Game logic
    if (game_state == _Running) {
        // Set active player for turn based
        if (is_turn_based) {
            if (players[0]->IsTurnOver()) {
                players[1]->SetActive();
            } else if (players[1]->IsTurnOver()) {
                players[0]->SetActive();
            }
        }

        // Gameover logic
        if (players[0]->IsDead() && players[1]->IsDead()) {
            winner_index = -1;
            game_state = _GameOver;
        } else if (players[1]->IsDead()) {
            winner_index = 0;
            game_state = _GameOver;
        } else if (players[0]->IsDead()) {
            winner_index = 1;
            game_state = _GameOver;
        }
    }
}

// Handle user input
void Application::ProcessInput() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            // Universal controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // Close window
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { // Pause
                if (game_state != _Paused) {
                    pre_paused_game_state = game_state;
                    game_state = _Paused;
                } else {
                    game_state = pre_paused_game_state;
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { // End game to start over
                game_state = _GameOver;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { // Debug, add budget
                for (unsigned int i = 0; i < players.size(); ++i) {
                    for (int n = 0; n < 10; ++n) {
                        players[i]->AddBudget();
                    }
                }
            }

            if (game_state == _MainMenu) {
                // Player 1 controls
                if (event.key.code == sf::Keyboard::Space) { // Fire
                    if (selected_p1_class == -1 || selected_p2_class == -1) {
                        selected_p1_class = main_menu->InputP1Select();
                    } else if (selected_map == -1) {
                        selected_map = main_menu->InputP1Select();
                        tile_map = new TileMap(selected_map);
                    }
                } else if (event.key.code == sf::Keyboard::Up) { // Up
                    main_menu->InputP1Up();
                } else if (event.key.code == sf::Keyboard::Down) { // Down
                    main_menu->InputP1Down();
                } else if (event.key.code == sf::Keyboard::Left) { // Left
                    main_menu->InputP1Left();
                } else if (event.key.code == sf::Keyboard::Right) { // Right
                    main_menu->InputP1Right();
                } else if (event.key.code == sf::Keyboard::RShift) { // Change projectile
                    // Nothing?
                } else if (event.key.code == sf::Keyboard::Equal) { // Increase power
                    // Cycle color up
                } else if (event.key.code == sf::Keyboard::Dash) { // Decrease power
                    // Cycle color down

                // Player 2 controls
                } else if (event.key.code == sf::Keyboard::Return) { // Fire
                    if (selected_p1_class == -1 || selected_p2_class == -1) {
                        selected_p2_class = main_menu->InputP2Select();
                    } else if (selected_map == -1) {
                        selected_map = main_menu->InputP2Select();
                        tile_map = new TileMap(selected_map);
                    }
                } else if (event.key.code == sf::Keyboard::Numpad8) { // Up
                    main_menu->InputP2Up();
                } else if (event.key.code == sf::Keyboard::Numpad5) { // Down
                    main_menu->InputP2Down();
                } else if (event.key.code == sf::Keyboard::Numpad4) { // Left
                    main_menu->InputP2Left();
                } else if (event.key.code == sf::Keyboard::Numpad6) { // Right
                    main_menu->InputP2Right();
                } else if (event.key.code == sf::Keyboard::Numpad7) { // Change projectile
                    // Nothing?
                } else if (event.key.code == sf::Keyboard::Numpad2) { // Increase power
                    // Cycle color up
                } else if (event.key.code == sf::Keyboard::Numpad0) { // Decrease power
                    // Cycle color down
                }
            } else if (game_state == _Running) {
                // Player 1 controls
                if (event.key.code == sf::Keyboard::Space) { // Fire
                    players[0]->InputFire();
                } else if (event.key.code == sf::Keyboard::Up) { // Up
                    players[0]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::Down) { // Down
                    players[0]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::Left) { // Left
                    players[0]->InputMoveLeft(tile_map);
                } else if (event.key.code == sf::Keyboard::Right) { // Right
                    players[0]->InputMoveRight(tile_map);
                } else if (event.key.code == sf::Keyboard::RShift) { // Change projectile
                    players[0]->InputCycleProjectileType();
                } else if (event.key.code == sf::Keyboard::Equal) { // Increase power
                    players[0]->InputPowerUp();
                } else if (event.key.code == sf::Keyboard::Dash) { // Decrease power
                    players[0]->InputPowerDown();

                // Player 2 controls
                } else if (event.key.code == sf::Keyboard::Return) { // Fire
                    players[1]->InputFire();
                } else if (event.key.code == sf::Keyboard::Numpad8) { // Up
                    players[1]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::Numpad5) { // Down
                    players[1]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::Numpad4) { // Left
                    players[1]->InputMoveLeft(tile_map);
                } else if (event.key.code == sf::Keyboard::Numpad6) { // Right
                    players[1]->InputMoveRight(tile_map);
                } else if (event.key.code == sf::Keyboard::Numpad7) { // Change projectile
                    players[1]->InputCycleProjectileType();
                } else if (event.key.code == sf::Keyboard::Numpad2) { // Increase power
                    players[1]->InputPowerUp();
                } else if (event.key.code == sf::Keyboard::Numpad0) { // Decrease power
                    players[1]->InputPowerDown();
                }
            } else if (game_state == _GameOver) {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return) {
                    CleanUp();
                    StartNewGame();
                }
            }
        }
    }
}

void Application::DrawElapsedTimeString() {
    text_elapsed_time.setString(elapsed_time_string);
    window.draw(text_elapsed_time);
}

// Deletes
void Application::CleanUp() {
    delete tile_map;

    delete main_menu;

    for (unsigned int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    players.clear();
}
