#include "Application.h"
#include "ParticleSystem.cpp"

Application::~Application() {}

Application::Application() {
    InitialSetup();

    ParticleSystem particles(10000);

    // Use a fixed time step
    static const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); // 60 fps
    sf::Clock clock;
    sf::Time elapsed_time;

    // Main game loop
    while (window.isOpen()) {
        elapsed_time = clock.restart();
        debug_string = "usec/frame: " + toString(elapsed_time.asMicroseconds()) + " / 16666";

        while (elapsed_time < TIME_PER_FRAME) {
            ProcessInput();
            elapsed_time += clock.restart();
        }

        //Render();

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        particles.update(elapsed_time);

        // draw it
        window.clear();
        window.draw(particles);
        debugString(debug_string, window, font);
        window.display();
    }
}

// Handle user input
void Application::ProcessInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) { // Left click
                sf::Vector2i position = sf::Mouse::getPosition(window);

                position.x = floor(position.x / TILE_SIZE);
                position.y = floor(position.y / TILE_SIZE);

                if (position.x < TERRAIN_SIZE_X && position.y < TERRAIN_SIZE_Y) {
                    terrain[position.y][position.x] = 1;
                }

                debug_string += toString(position.x) + " " + toString(position.y);
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
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
            break;
        case Paused:
            break;
        default:
            debug_string = "Game state error";
            break;
    }

    debugString(debug_string, window, font);
    window.display();
}

// Update terrain using 2D array and tiles
void Application::UpdateTerrain() {
    for (int y = 0; y < TERRAIN_SIZE_Y; ++y) {
        for (int x = 0; x < TERRAIN_SIZE_X; ++x) {
            switch (terrain[y][x]) {
            case 0:
                terrain_tile.setFillColor(sf::Color(63, 63, 63, 255)); // RGBA (red, green, blue, transparency)
                break;
            case 1:
                continue;
                break;
            default:
                break;
            }
            terrain_tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(terrain_tile);
        }
    }
}

// Load files and set all starting states and defaults
void Application::InitialSetup() {
    // Create window
    window.create(sf::VideoMode(1600, 800), "Dank Tanks!");

    // Load a font for sf::Text
    font.loadFromFile("Cousine-Regular.ttf");

    // Initialize game state
    game_state = Running;

    // Initialize terrain array
    for (int y = 0; y < TERRAIN_SIZE_Y; ++y) {
        for (int x = 0; x < TERRAIN_SIZE_X; ++x) {
            terrain[y][x] = 0;
        }
    }

    // Create tile for terrain
    terrain_tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    terrain_tile.setFillColor(sf::Color::Black);
    terrain_tile.setOutlineColor(sf::Color(127, 127, 127, 255));
    terrain_tile.setOutlineThickness(1);
}
