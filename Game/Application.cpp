#include "Application.h"

Application::~Application() {
    delete tileMap;

    for (unsigned int i = 0; i < projectile_vector.size(); i++) {
        delete projectile_vector[i];
    }
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
        debug_string = toString(elapsed_time.asMicroseconds()) + " / 16666";

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
            } else if (event.key.code == sf::Keyboard::Space) { // Space bar
                projectile_vector.push_back(new Projectile());
            } else if (event.key.code == sf::Keyboard::P) { // "P" key pressed
                if (game_state == Running) {
                    game_state = Paused;
                } else {
                    game_state = Running;
                }
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
            UpdateProjectiles();
            debugString(debug_string, window, font);
            break;
        case Paused:
            break;
        default:
            debug_string = "Game state error";
            debugString(debug_string, window, font);
            break;
    }

    window.display();
}

// Update terrain using 2D array and tiles
void Application::UpdateTerrain() {
    tileMap->Update(window);
}

void Application::UpdateProjectiles() {
    for (unsigned int i = 0; i < projectile_vector.size(); i++) {
        projectile_vector[i]->Update(window, tileMap);

        if (projectile_vector[i]->isExpired()) {
            delete projectile_vector[i];
            projectile_vector.erase(projectile_vector.begin() + i);
        }
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

    tileMap = new TileMap();
}
