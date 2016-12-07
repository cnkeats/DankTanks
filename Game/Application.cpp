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
        debug_string = toString(elapsed_time.asMicroseconds()) + " / 16666 ";

        while (elapsed_time < TIME_PER_FRAME) {
            ProcessInput();
            elapsed_time += clock.restart();
        }

        Render();
    }
}

// Handle user input
void Application::ProcessInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } else if (event.key.code == sf::Keyboard::P) { // "P" key pressed
                if (game_state == Running) {
                    game_state = Paused;
                } else {
                    game_state = Running;
                }
            } else if (event.key.code == sf::Keyboard::Space) {
                players[0]->InputFire(0);
            } else if (event.key.code == sf::Keyboard::Up) {
                players[0]->InputRotate(-1);
            } else if (event.key.code == sf::Keyboard::Down) {
                players[0]->InputRotate(1);
            } else if (event.key.code == sf::Keyboard::Right) {
                players[0]->InputMove(1);
            } else if (event.key.code == sf::Keyboard::Left) {
                players[0]->InputMove(-1);
            }
        }
    }
}

// Render based on game state
void Application::Render() {
    switch (game_state) {
        case Running:
            window.clear(sf::Color(sf::Color::Black));
            UpdateTerrain();
            UpdatePlayers();
            debugString(debug_string);
            break;
        case Paused:
            break;
        default:
            debug_string = "Game state error";
            debugString(debug_string);
            break;
    }

    window.display();
}

// Update terrain using 2D array and tiles
void Application::UpdateTerrain() {
    tileMap->Update();
    window.draw(*tileMap);
}

void Application::UpdatePlayers() {
    for (unsigned int i = 0; i < players.size(); ++i) {
        players[i]->Update(tileMap);
    }
}

// Load files and set all starting states and defaults
void Application::InitialSetup() {
    // Create window
    window.create(sf::VideoMode(1, 1), "Dank Tanks!", sf::Style::Fullscreen);

    // Load a font for sf::Text
    font.loadFromFile("Cousine-Regular.ttf");

    // Initialize game state
    game_state = Running;

    // Create map
    tileMap = new TileMap();

    // Create players
    players.push_back(new Player(sf::Vector2f(10 * TILE_SIZE, (TILES_Y - 51) * TILE_SIZE)));
    players.push_back(new Player(sf::Vector2f(118 * TILE_SIZE, (TILES_Y - 51) * TILE_SIZE)));
}
