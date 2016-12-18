#include "Application.h"

Application::~Application() {
    delete tileMap;
}

Application::Application() {
    InitialSetup();

    // Use a fixed time step
    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); // 60 fps
    sf::Clock clock;
    sf::Time elapsed_time;

    // Main game loop
    while (window.isOpen()) {
        elapsed_time = clock.restart();
        //debug_string = toString(elapsed_time.asMicroseconds()) + " / 16666 ";
        debug_string = "";

        while (elapsed_time < TIME_PER_FRAME) {
            ProcessInput();
            elapsed_time += clock.restart();
        }

        Render();
    }
}

// Render based on game state
void Application::Render() {
    switch (game_state) {
        case _MainMenuMap:
            window.clear(sf::Color(sf::Color(69, 69, 69, 255)));
            UpdateMainMenu();
            debugString(debug_string);
            break;
        case _MainMenuColor:
            window.clear(sf::Color(sf::Color(69, 69, 69, 255)));
            UpdateMainMenu();
            debugString(debug_string);
            break;
        case _RunningP1Turn:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            debugString(debug_string);
            break;
        case _RunningP2Turn:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            debugString(debug_string);
            break;
        case _RunningRealTime:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            debugString(debug_string);
            break;
        default:
            debug_string = "Game state error";
            debugString(debug_string);
            break;
    }

    window.display();
}

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

        if (players[i]->IsDead()) {
            debug_string += " players[" + toString(i) + "] is dead.";
        }
    }

    if (game_state == _RunningP1Turn) {
        players[0]->UpdateInfo();
    } else if (game_state == _RunningP2Turn) {
        players[1]->UpdateInfo();
    }

    if (game_state == _RunningRealTime) {
        players[0]->UpdateInfo();
    }
}

// Load files and set all starting states and defaults
void Application::InitialSetup() {
    // Create window
    window.create(sf::VideoMode(1, 1), "Dank Tanks!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    // Load a font for sf::Text
    font.loadFromFile("Cousine-Regular.ttf");

    // Initialize game state
    game_state = _MainMenuMap;

    // Create menu
    mainMenu = new MainMenu();

    // Create players
    players.push_back(new Player(sf::Vector2f(15 * TILE_SIZE, 0)));
    players.push_back(new Player(sf::Vector2f((TILES_X - 15) * TILE_SIZE, 0)));

    selected_p1_color = sf::Vector2i(-1, -1);
    selected_p2_color = sf::Vector2i(-1, -1);
}

// Handle user input
void Application::ProcessInput() {
    sf::Event event;

    if (game_state == _MainMenuMap) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    selected_map = mainMenu->InputP1Select();
                    tileMap = new TileMap(selected_map);
                    game_state = _MainMenuColor;
                } else if (event.key.code == sf::Keyboard::Up) {
                    mainMenu->InputP1Up();
                } else if (event.key.code == sf::Keyboard::Down) {
                    mainMenu->InputP1Down();
                } else if (event.key.code == sf::Keyboard::Left) {
                    mainMenu->InputP1Left();
                } else if (event.key.code == sf::Keyboard::Right) {
                    mainMenu->InputP1Right();
                }
            }
        }
    } else if (game_state == _MainMenuColor) {
        if (selected_p1_color != sf::Vector2i(-1, -1) && selected_p2_color != sf::Vector2i(-1, -1)) {
            game_state = _RunningP1Turn;
            //game_state = _RunningRealTime;
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    selected_p1_color = mainMenu->InputP1Select();
                    players[0]->SetColor(selected_p1_color);
                } else if (event.key.code == sf::Keyboard::Up) {
                    mainMenu->InputP1Up();
                } else if (event.key.code == sf::Keyboard::Down) {
                    mainMenu->InputP1Down();
                } else if (event.key.code == sf::Keyboard::Left) {
                    mainMenu->InputP1Left();
                } else if (event.key.code == sf::Keyboard::Right) {
                    mainMenu->InputP1Right();

                } else if (event.key.code == sf::Keyboard::LControl) {
                    selected_p2_color = mainMenu->InputP2Select();
                    players[1]->SetColor(selected_p2_color);
                } else if (event.key.code == sf::Keyboard::W) {
                    mainMenu->InputP2Up();
                } else if (event.key.code == sf::Keyboard::S) {
                    mainMenu->InputP2Down();
                } else if (event.key.code == sf::Keyboard::A) {
                    mainMenu->InputP2Left();
                } else if (event.key.code == sf::Keyboard::D) {
                    mainMenu->InputP2Right();
                }
            }
        }
    } else if (game_state == _RunningP1Turn) {
        if (players[0]->IsTurnOver()) {
            game_state = _RunningP2Turn;
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    players[0]->InputFire();
                } else if (event.key.code == sf::Keyboard::Up) {
                    players[0]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::Down) {
                    players[0]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::Left) {
                    players[0]->InputMoveLeft(tileMap);
                } else if (event.key.code == sf::Keyboard::Right) {
                    players[0]->InputMoveRight(tileMap);
                } else if (event.key.code == sf::Keyboard::Num0) {
                    players[0]->InputSetProjectileType(0);
                } else if (event.key.code == sf::Keyboard::Num1) {
                    players[0]->InputSetProjectileType(1);
                } else if (event.key.code == sf::Keyboard::Num2) {
                    players[0]->InputSetProjectileType(2);
                } else if (event.key.code == sf::Keyboard::Num3) {
                    players[0]->InputSetProjectileType(3);
                } else if (event.key.code == sf::Keyboard::Num4) {
                    players[0]->InputSetProjectileType(4);
                } else if (event.key.code == sf::Keyboard::Num5) {
                    players[0]->InputSetProjectileType(5);
                } else if (event.key.code == sf::Keyboard::Num6) {
                    players[0]->InputSetProjectileType(6);
                } else if (event.key.code == sf::Keyboard::Num7) {
                    players[0]->InputSetProjectileType(7);
                } else if (event.key.code == sf::Keyboard::Num8) {
                    players[0]->InputSetProjectileType(8);
                } else if (event.key.code == sf::Keyboard::Num9) {
                    players[0]->InputSetProjectileType(9);
                }
            }
        }
    } else if (game_state == _RunningP2Turn) {
        if (players[1]->IsTurnOver()) {
            game_state = _RunningP1Turn;
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Num0) {
                    players[1]->InputSetProjectileType(0);
                } else if (event.key.code == sf::Keyboard::Num1) {
                    players[1]->InputSetProjectileType(1);
                } else if (event.key.code == sf::Keyboard::Num2) {
                    players[1]->InputSetProjectileType(2);
                } else if (event.key.code == sf::Keyboard::Num3) {
                    players[1]->InputSetProjectileType(3);
                } else if (event.key.code == sf::Keyboard::Num4) {
                    players[1]->InputSetProjectileType(4);
                } else if (event.key.code == sf::Keyboard::Num5) {
                    players[1]->InputSetProjectileType(5);
                } else if (event.key.code == sf::Keyboard::Num6) {
                    players[1]->InputSetProjectileType(6);
                } else if (event.key.code == sf::Keyboard::Num7) {
                    players[1]->InputSetProjectileType(7);
                } else if (event.key.code == sf::Keyboard::Num8) {
                    players[1]->InputSetProjectileType(8);
                } else if (event.key.code == sf::Keyboard::Num9) {
                    players[1]->InputSetProjectileType(9);

                } else if (event.key.code == sf::Keyboard::LControl) {
                    players[1]->InputFire();
                } else if (event.key.code == sf::Keyboard::W) {
                    players[1]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::S) {
                    players[1]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::A) {
                    players[1]->InputMoveLeft(tileMap);
                } else if (event.key.code == sf::Keyboard::D) {
                    players[1]->InputMoveRight(tileMap);
                }
            }
        }
    } else if (game_state == _RunningRealTime) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    players[0]->InputFire();
                } else if (event.key.code == sf::Keyboard::Up) {
                    players[0]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::Down) {
                    players[0]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::Left) {
                    players[0]->InputMoveLeft(tileMap);
                } else if (event.key.code == sf::Keyboard::Right) {
                    players[0]->InputMoveRight(tileMap);
                } else if (event.key.code == sf::Keyboard::Num0) {
                    players[0]->InputSetProjectileType(0);
                } else if (event.key.code == sf::Keyboard::Num1) {
                    players[0]->InputSetProjectileType(1);
                } else if (event.key.code == sf::Keyboard::Num2) {
                    players[0]->InputSetProjectileType(2);
                } else if (event.key.code == sf::Keyboard::Num3) {
                    players[0]->InputSetProjectileType(3);
                } else if (event.key.code == sf::Keyboard::Num4) {
                    players[0]->InputSetProjectileType(4);
                } else if (event.key.code == sf::Keyboard::Num5) {
                    players[0]->InputSetProjectileType(5);
                } else if (event.key.code == sf::Keyboard::Num6) {
                    players[0]->InputSetProjectileType(6);
                } else if (event.key.code == sf::Keyboard::Num7) {
                    players[0]->InputSetProjectileType(7);
                } else if (event.key.code == sf::Keyboard::Num8) {
                    players[0]->InputSetProjectileType(8);
                } else if (event.key.code == sf::Keyboard::Num9) {
                    players[0]->InputSetProjectileType(9);

                } else if (event.key.code == sf::Keyboard::LControl) {
                    players[1]->InputFire();
                } else if (event.key.code == sf::Keyboard::W) {
                    players[1]->InputRotateClockwise();
                } else if (event.key.code == sf::Keyboard::S) {
                    players[1]->InputRotateCounterClockwise();
                } else if (event.key.code == sf::Keyboard::A) {
                    players[1]->InputMoveLeft(tileMap);
                } else if (event.key.code == sf::Keyboard::D) {
                    players[1]->InputMoveRight(tileMap);
                }
            }
        }
    }
}
