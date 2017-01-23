#include "Application.h"
//#include "wiringPi.h" // Required on pi

Application::~Application() {
    CleanUp();
}

// Main game loop
Application::Application() {
    // Required on pi
    //if (wiringPiSetupGpio() == -1) {
        //TODO
    //}

    window.create(sf::VideoMode(1, 1), "Dank Tanks!", sf::Style::Fullscreen); // Create window
    window.setMouseCursorVisible(false);

    font.loadFromFile("Cousine-Regular.ttf"); // Load a font for sf::Text

    StartNewMenu();

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
void Application::StartNewMenu() {
    game_state = _MainMenu; // Initialize game state

    main_menu = new MainMenu(); // Create menu

    is_turn_based = false;

    game_starter.Reset();

    winner_index = -2;

    text_elapsed_time.setFont(font);
    text_elapsed_time.setCharacterSize(20);
    text_elapsed_time.setColor(sf::Color::White);
    text_elapsed_time.setPosition(window.getSize().x - 180, 0);
}

void Application::StartNewGame() {
    game_state = _Running;

    // Create map
    tile_map = new TileMap(game_starter.map_index);

    // Create players
    players.clear();
    players.push_back(new Player(0, is_turn_based, game_starter.p1_class_index, game_starter.p1_color_index, sf::Vector2f(8 * TILE_SIZE, 0)));
    players.push_back(new Player(1, is_turn_based, game_starter.p2_class_index, game_starter.p2_color_index, sf::Vector2f((TILES_X - 10) * TILE_SIZE, 0)));

    players[0]->SetActive();
    game_clock.restart();
    game_budget_clock.restart();
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
    /*sf::Event event;

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
                if (game_state == _Running) {
                    game_state = _GameOver;
                }
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
                    game_starter = main_menu->InputP1Select();

                    if (game_starter.map_index != -1) {
                        StartNewGame();
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
                    main_menu->InputP1Back();
                } else if (event.key.code == sf::Keyboard::Equal) { // Increase power
                    // Cycle color up
                } else if (event.key.code == sf::Keyboard::Dash) { // Decrease power
                    // Cycle color down

                // Player 2 controls
                } else if (event.key.code == sf::Keyboard::Return) { // Fire
                    game_starter = main_menu->InputP2Select();

                    if (game_starter.map_index != -1) {
                        StartNewGame();
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
                    main_menu->InputP2Back();
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
                    StartNewMenu();
                }
            }
        }
    }*/


    // Universal controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // Close window
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { // Pause
        if (game_state != _Paused) {
            pre_paused_game_state = game_state;
            game_state = _Paused;
        } else {
            game_state = pre_paused_game_state;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { // End game to start over
        if (game_state == _Running) {
            game_state = _GameOver;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { // Debug, add budget
        for (unsigned int i = 0; i < players.size(); ++i) {
            for (int n = 0; n < 10; ++n) {
                players[i]->AddBudget();
            }
        }
    }

    if (game_state == _MainMenu) {
        // Player 1 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Fire
            game_starter = main_menu->InputP1Select();

            if (game_starter.map_index != -1) {
                StartNewGame();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // Up
            main_menu->InputP1Up();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Down
            main_menu->InputP1Down();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // Left
            main_menu->InputP1Left();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // Right
            main_menu->InputP1Right();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) { // Change projectile
            main_menu->InputP1Back();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) { // Increase power
            // Cycle color up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) { // Decrease power
            // Cycle color down
        }

        // Player 2 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // Fire
            game_starter = main_menu->InputP2Select();

            if (game_starter.map_index != -1) {
                StartNewGame();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) { // Up
            main_menu->InputP2Up();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) { // Down
            main_menu->InputP2Down();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) { // Left
            main_menu->InputP2Left();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) { // Right
            main_menu->InputP2Right();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) { // Change projectile
            main_menu->InputP2Back();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { // Increase power
            // Cycle color up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) { // Decrease power
            // Cycle color down
        }
    } else if (game_state == _Running) {
        // Player 1 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // Left
            players[0]->Input(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // Right
            players[0]->Input(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // Up
            players[0]->Input(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Down
            players[0]->Input(3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Fire
            players[0]->Input(4);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) { // Increase power
            players[0]->Input(5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) { // Change projectile
            players[0]->Input(6);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) { // Decrease power
            players[0]->Input(7);
        }

        // Player 2 controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) { // Left
            players[1]->Input(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) { // Right
            players[1]->Input(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) { // Up
            players[1]->Input(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) { // Down
            players[1]->Input(3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // Fire
            players[1]->Input(4);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { // Increase power
            players[1]->Input(5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) { // Change projectile
            players[1]->Input(6);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) { // Decrease power
            players[1]->Input(7);
        }
    } else if (game_state == _GameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            CleanUp();
            StartNewMenu();
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
}
