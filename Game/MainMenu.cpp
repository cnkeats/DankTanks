#include "MainMenu.h"

MainMenu::~MainMenu() {
    for (unsigned int i = 0; i < selector_textures.size(); ++i) {
        delete selector_textures[i];
    }

    for (unsigned int i = 0; i < selectors.size(); ++i) {
        delete selectors[i];
    }

    for (unsigned int i = 0; i < class_textures.size(); ++i) {
        delete class_textures[i];
    }

    for (unsigned int i = 0; i < class_tiles.size(); ++i) {
        delete class_tiles[i];
    }

    for (unsigned int i = 0; i < class_preview_textures.size(); ++i) {
        delete class_preview_textures[i];
    }

    for (unsigned int i = 0; i < class_previews.size(); ++i) {
        delete class_previews[i];
    }

    for (unsigned int i = 0; i < map_textures.size(); ++i) {
        delete map_textures[i];
    }

    for (unsigned int i = 0; i < map_tiles.size(); ++i) {
        delete map_tiles[i];
    }

    for (unsigned int i = 0; i < map_preview_textures.size(); ++i) {
        delete map_preview_textures[i];
    }
}

MainMenu::MainMenu() {
    PopulateClasses();
}

// Main game loop calls this update function
void MainMenu::Update() {
    // If both players have selected a class, go to map selection
    if (menu_state == _SelectingClass && game_starter.ClassesAreSelected()) {
        PopulateMaps();
    }

    UpdateInput();

    if (menu_state == _SelectingClass) {
        debug_string += "Select Color (Player 1 and 2)";

        // Class tiles at bottom
        for (unsigned int i = 0; i < class_tiles.size(); ++i) {
            window.draw(*class_tiles[i]);
        }

        // Class previews at top
        for (unsigned int i = 0; i < class_previews.size(); ++i) {
            window.draw(*class_previews[i]);
        }

        window.draw(p1_color_rectangle);
        window.draw(p2_color_rectangle);
    } else if (menu_state == _SelectingMap) {
        debug_string += "Select Map";

        // Map tiles at bottom
        for (unsigned int i = 0; i < map_tiles.size(); ++i) {
            window.draw(*map_tiles[i]);
        }

        // Map preview at top
        window.draw(map_preview);
    }

    // Selectors at bottom
    for (unsigned int i = 0; i < selectors.size(); ++i) {
        window.draw(*selectors[i]);
    }

    debug_string += "\n" + game_starter.toString();
}

// Update input
void MainMenu::UpdateInput() {
    // Decrease cooldown counters
    for (int i = 0; i < 8; ++i) {
        if (p1_input_cooldown[i] > 0) {
            --p1_input_cooldown[i];
        }

        if (p2_input_cooldown[i] > 0) {
            --p2_input_cooldown[i];
        }
    }

    // P1
    // Input is queued and takes action now
    if (p1_input_status[0] && p1_input_cooldown[0] == 0) { // (left)
        p1_input_status[0] = false;
        p1_input_cooldown[0] = 10;
        InputP1Left();
    }

    // Input is
    if (p1_input_status[1] && p1_input_cooldown[1] == 0) { // (right)
        p1_input_status[1] = false;
        p1_input_cooldown[1] = 10;
        InputP1Right();
    }

    // Input is
    if (p1_input_status[2] && p1_input_cooldown[2] == 0) { // (up)
        p1_input_status[2] = false;
        p1_input_cooldown[2] = 10;
        InputP1Up();
    }

    // Input is
    if (p1_input_status[3] && p1_input_cooldown[3] == 0) { // (down)
        p1_input_status[3] = false;
        p1_input_cooldown[3] = 10;
        InputP1Down();
    }

    // There's a spot for [4] but select is different so it's left out

    // Input is
    if (p1_input_status[5] && p1_input_cooldown[5] == 0) { // (top right)
        p1_input_status[5] = false;
        p1_input_cooldown[5] = 10;
        InputP1ColorUp();
    }

    // Input is
    if (p1_input_status[6] && p1_input_cooldown[6] == 0) { // (bottom left)
        p1_input_status[6] = false;
        p1_input_cooldown[6] = 10;
        InputP1Back();
    }

    // Input is
    if (p1_input_status[7] && p1_input_cooldown[7] == 0) { // (bottom right)
        p1_input_status[7] = false;
        p1_input_cooldown[7] = 10;
        InputP1ColorDown();
    }

    // P2
    // Input is queued and takes action now
    if (p2_input_status[0] && p2_input_cooldown[0] == 0) { // (left)
        p2_input_status[0] = false;
        p2_input_cooldown[0] = 10;
        InputP2Left();
    }

    // Input is
    if (p2_input_status[1] && p2_input_cooldown[1] == 0) { // (right)
        p2_input_status[1] = false;
        p2_input_cooldown[1] = 10;
        InputP2Right();
    }

    // Input is
    if (p2_input_status[2] && p2_input_cooldown[2] == 0) { // (up)
        p2_input_status[2] = false;
        p2_input_cooldown[2] = 10;
        InputP2Up();
    }

    // Input is
    if (p2_input_status[3] && p2_input_cooldown[3] == 0) { // (down)
        p2_input_status[3] = false;
        p2_input_cooldown[3] = 10;
        InputP2Down();
    }

    // There's a spot for [4] but select is different so it's left out

    // Input is
    if (p2_input_status[5] && p2_input_cooldown[5] == 0) { // (top right)
        p2_input_status[5] = false;
        p2_input_cooldown[5] = 10;
        InputP2ColorUp();
    }

    // Input is
    if (p2_input_status[6] && p2_input_cooldown[6] == 0) { // (bottom left)
        p2_input_status[6] = false;
        p2_input_cooldown[6] = 10;
        InputP2Back();
    }

    // Input is
    if (p2_input_status[7] && p2_input_cooldown[7] == 0) { // (bottom right)
        p2_input_status[7] = false;
        p2_input_cooldown[7] = 10;
        InputP2ColorDown();
    }
}

// Change texture of menu tiles, position is unchanged
void MainMenu::PopulateClasses() {
    menu_state = _SelectingClass;

    // New
    if (class_textures.size() == 0) {
        // Classes at bottom (textures and rectangles)
        for (unsigned int i = 0; i < 4; ++i) {
            class_textures.push_back(new sf::Texture);
            if (!class_textures[i]->loadFromFile("menu_class.png", sf::IntRect(i * THUMBNAIL_SIZE_X, 0, THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y))) {
                //TODO
            }

            // Create bottom list of classes
            class_tiles.push_back(new sf::RectangleShape);
            class_tiles[i]->setSize(sf::Vector2f(THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y));
            class_tiles[i]->setPosition(sf::Vector2f(PADDING + i * (THUMBNAIL_SIZE_X + PADDING), window.getSize().y - THUMBNAIL_SIZE_Y - PADDING));
            class_tiles[i]->setTexture(class_textures[i]);
        }

        // Selectors (textures and rectangles)
        for (unsigned int i = 0; i < 4; ++i) {
            selector_textures.push_back(new sf::Texture);
            if (!selector_textures[i]->loadFromFile("menu_class.png", sf::IntRect(i * THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y, THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y))) {
                //TODO
            }

            // Create bottom list of classes
            selectors.push_back(new sf::RectangleShape);
            selectors[i]->setSize(sf::Vector2f(THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y));
            selectors[i]->setPosition(sf::Vector2f(PADDING, window.getSize().y - THUMBNAIL_SIZE_Y - PADDING));
            selectors[i]->setTexture(selector_textures[i]);
        }

        // Class previews at top (textures)
        for (unsigned int y = 0; y < 2; ++y) {
            for (unsigned int x = 0; x < 2; ++x) {
                class_preview_textures.push_back(new sf::Texture);
                if (!class_preview_textures[x + y * 2]->loadFromFile("menu_class_preview.png", sf::IntRect(x * CLASS_PREVIEW_SIZE_X, y * CLASS_PREVIEW_SIZE_Y, CLASS_PREVIEW_SIZE_X, CLASS_PREVIEW_SIZE_Y))) {
                    //TODO
                }
            }
        }

        // Class previews at top (rectangles)
        for (unsigned int i = 0; i < 2; ++i) {
            class_previews.push_back(new sf::RectangleShape);
            class_previews[i]->setSize(sf::Vector2f(CLASS_PREVIEW_SIZE_X, CLASS_PREVIEW_SIZE_Y));
            class_previews[i]->setPosition(sf::Vector2f(PADDING + i * (CLASS_PREVIEW_SIZE_X + PADDING), PADDING));
            class_previews[i]->setTexture(class_preview_textures[i]);
        }
    }

    p1_selected = 0;
    p2_selected = 0;

    game_starter.Reset();

    p1_color_rectangle.setSize(sf::Vector2f(50, 50));
    p1_color_rectangle.setPosition(sf::Vector2f(PADDING, PADDING));
    p1_color_rectangle.setOutlineColor(sf::Color::Black);
    p1_color_rectangle.setOutlineThickness(-1);
    SetColor(p1_color_rectangle, game_starter.p1_color_index);

    p2_color_rectangle.setSize(sf::Vector2f(50, 50));
    p2_color_rectangle.setPosition(sf::Vector2f(CLASS_PREVIEW_SIZE_X + PADDING * 2, PADDING));
    p2_color_rectangle.setFillColor(sf::Color(51, 255, 255, 255));
    p2_color_rectangle.setOutlineColor(sf::Color::Black);
    p2_color_rectangle.setOutlineThickness(-1);
    SetColor(p2_color_rectangle, game_starter.p2_color_index);

    UpdateP1Selection();
    UpdateP2Selection();

    for (int i = 0; i < 8; ++i) {
        p1_input_status[i] = false;
        p1_input_cooldown[i] = 10;
    }
}

// Populate menu boxes that will be drawn when this object is drawn
void MainMenu::PopulateMaps() {
    menu_state = _SelectingMap;

    // New
    if (map_textures.size() == 0) {
        // Maps at bottom (textures and rectangles)
        for (unsigned int i = 0; i < 4; ++i) {
            map_textures.push_back(new sf::Texture);
            if (!map_textures[i]->loadFromFile("menu_map.png", sf::IntRect(i * THUMBNAIL_SIZE_X, 0, THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y))) {
                //TODO
            }

            // Create bottom list of classes
            map_tiles.push_back(new sf::RectangleShape);
            map_tiles[i]->setSize(sf::Vector2f(THUMBNAIL_SIZE_X, THUMBNAIL_SIZE_Y));
            map_tiles[i]->setPosition(sf::Vector2f(PADDING + i * (THUMBNAIL_SIZE_X + PADDING), window.getSize().y - THUMBNAIL_SIZE_Y - PADDING));
            map_tiles[i]->setTexture(map_textures[i]);
        }

        // Map preview at top (textures)
        for (unsigned int y = 0; y < 2; ++y) {
            for (unsigned int x = 0; x < 2; ++x) {
                map_preview_textures.push_back(new sf::Texture);
                if (!map_preview_textures[x + y * 2]->loadFromFile("menu_map_preview.png", sf::IntRect(x * MAP_PREVIEW_SIZE_X, y * MAP_PREVIEW_SIZE_Y, MAP_PREVIEW_SIZE_X, MAP_PREVIEW_SIZE_Y))) {
                    //TODO
                }
            }
        }

        // Map preview at top (rectangle)
        map_preview.setSize(sf::Vector2f(MAP_PREVIEW_SIZE_X, MAP_PREVIEW_SIZE_Y));
        map_preview.setPosition(sf::Vector2f(448, PADDING));
        map_preview.setTexture(map_preview_textures[0]);
    }

    p1_selected = 0;
    p2_selected = 0;

    UpdateP1Selection();
    UpdateP2Selection();

    for (int i = 0; i < 8; ++i) {
        p1_input_status[i] = false;
        p1_input_cooldown[i] = 10;
    }
}

// Make menu movements wrap around all sides
void MainMenu::UpdateP1Selection() {
    if (p1_selected < 0) {
        p1_selected = MENU_X - 1;
    } else if (p1_selected >= MENU_X) {
        p1_selected = 0;
    }

    selectors[0]->setPosition(sf::Vector2f(PADDING + p1_selected * (THUMBNAIL_SIZE_X + PADDING), window.getSize().y - THUMBNAIL_SIZE_Y - PADDING));

    if (menu_state == _SelectingClass) {
        class_previews[0]->setTexture(class_preview_textures[p1_selected]);
    } else if (menu_state == _SelectingMap) {
        map_preview.setTexture(map_preview_textures[p1_selected]);
    }
}

// Make menu movements wrap around all sides
void MainMenu::UpdateP2Selection() {
    if (p2_selected < 0) {
        p2_selected = MENU_X - 1;
    } else if (p2_selected >= MENU_X) {
        p2_selected = 0;
    }

    selectors[1]->setPosition(sf::Vector2f(PADDING + p2_selected * (THUMBNAIL_SIZE_X + PADDING), window.getSize().y - THUMBNAIL_SIZE_Y - PADDING));

    if (menu_state == _SelectingClass) {
        class_previews[1]->setTexture(class_preview_textures[p2_selected]);
    } else if (menu_state == _SelectingMap) {
        map_preview.setTexture(map_preview_textures[p2_selected]);
    }
}

// Input for all P1
void MainMenu::InputP1(int input_index) {
    if (p1_input_cooldown[input_index] < 2) {
        p1_input_status[input_index] = true;
    }
}

// Move P1's selection left
void MainMenu::InputP1Left() {
    if (menu_state == _SelectingClass && game_starter.p1_class_index == -1) {
        p1_selected--;
        UpdateP1Selection();
    } else if (menu_state == _SelectingMap) {
        p1_selected--;
        p2_selected--;
        UpdateP1Selection();
        UpdateP2Selection();
    }
}

// Move P1's selection right
void MainMenu::InputP1Right() {
    if (menu_state == _SelectingClass && game_starter.p1_class_index == -1) {
        p1_selected++;
        UpdateP1Selection();
    } else if (menu_state == _SelectingMap) {
        p1_selected++;
        p2_selected++;
        UpdateP1Selection();
        UpdateP2Selection();
    }
}

// Move P1's selection up
void MainMenu::InputP1Up() {
    //p1_selected.y++;
}

// Move P1's selection down
void MainMenu::InputP1Down() {
    //p1_selected.y--;
}

// Return P1's current selected coordinates
GameStartingInfo MainMenu::InputP1Select() {
    if (p1_input_cooldown[4] == 0) {
        p1_input_cooldown[4] = 10;

        if (menu_state == _SelectingClass) {
            game_starter.p1_class_index = p1_selected;
        } else if (menu_state == _SelectingMap) {
            game_starter.map_index = p1_selected;
        }
    }

    return game_starter;
}

// Input P1's color up
void MainMenu::InputP1ColorUp() {
    if (menu_state == _SelectingClass && game_starter.p1_class_index == -1) {
        game_starter.p1_color_index++;

        if (game_starter.p1_color_index > 7) {
            game_starter.p1_color_index = 0;
        }

        SetColor(p1_color_rectangle, game_starter.p1_color_index);
    } else if (menu_state == _SelectingMap) {
        //
    }
}

// Input P1's back button
void MainMenu::InputP1Back() {
    if (menu_state == _SelectingClass) {
        game_starter.p1_class_index = -1;
    } else if (menu_state == _SelectingMap) {
        PopulateClasses();
    }
}

// Input P1's color down
void MainMenu::InputP1ColorDown() {
    if (menu_state == _SelectingClass && game_starter.p1_class_index == -1) {
        game_starter.p1_color_index--;

        if (game_starter.p1_color_index < 0) {
            game_starter.p1_color_index = 7;
        }

        SetColor(p1_color_rectangle, game_starter.p1_color_index);
    } else if (menu_state == _SelectingMap) {
        //
    }
}

// Input for all P2
void MainMenu::InputP2(int input_index) {
    if (p2_input_cooldown[input_index] < 2) {
        p2_input_status[input_index] = true;
    }
}

// Move P2's selection left
void MainMenu::InputP2Left() {
    if (menu_state == _SelectingClass && game_starter.p2_class_index == -1) {
        p2_selected--;
        UpdateP2Selection();
    } else if (menu_state == _SelectingMap) {
        p1_selected--;
        p2_selected--;
        UpdateP1Selection();
        UpdateP2Selection();
    }
}

// Move P2's selection right
void MainMenu::InputP2Right() {
    if (menu_state == _SelectingClass && game_starter.p2_class_index == -1) {
        p2_selected++;
        UpdateP2Selection();
    } else if (menu_state == _SelectingMap) {
        p1_selected++;
        p2_selected++;
        UpdateP1Selection();
        UpdateP2Selection();
    }
}

// Move P2's selection up
void MainMenu::InputP2Up() {
    if (menu_state == _SelectingClass) {
        //p2_selected.y++;
    } else if (menu_state == _SelectingMap) {
        //p1_selected.y++;
    }
}

// Move P2's selection down
void MainMenu::InputP2Down() {
    if (menu_state == _SelectingClass) {
        //p2_selected.y--;
    } else if (menu_state == _SelectingMap) {
        //p1_selected.y--;
    }
}

// Return P2's current selected coordinates
GameStartingInfo MainMenu::InputP2Select() {
    if (p2_input_cooldown[4] == 0) {
        p2_input_cooldown[4] = 10;

        if (menu_state == _SelectingClass) {
            game_starter.p2_class_index = p2_selected;
        } else if (menu_state == _SelectingMap) {
            game_starter.map_index = p2_selected;
        }
    }

    return game_starter;
}

// Input P2's color down
void MainMenu::InputP2ColorUp() {
    if (menu_state == _SelectingClass && game_starter.p2_class_index == -1) {
        game_starter.p2_color_index++;

        if (game_starter.p2_color_index > 7) {
            game_starter.p2_color_index = 0;
        }

        SetColor(p2_color_rectangle, game_starter.p2_color_index);
    } else if (menu_state == _SelectingMap) {
        //
    }
}

// Input P2's back button
void MainMenu::InputP2Back() {
    if (menu_state == _SelectingClass) {
        game_starter.p2_class_index = -1;
    } else if (menu_state == _SelectingMap) {
        PopulateClasses();
    }
}

// Input P2's color down
void MainMenu::InputP2ColorDown() {
    if (menu_state == _SelectingClass && game_starter.p2_class_index == -1) {
        game_starter.p2_color_index--;

        if (game_starter.p2_color_index < 0) {
            game_starter.p2_color_index = 7;
        }

        SetColor(p2_color_rectangle, game_starter.p2_color_index);
    } else if (menu_state == _SelectingMap) {
        //
    }
}

// Set the player's color
void MainMenu::SetColor(sf::RectangleShape &r, int i) {
    sf::Color color;

    // A truth table of colors!
    switch (i) {
        case 0:
            r.setFillColor(sf::Color(51, 255, 255, 255)); // cyan
            r.setOutlineColor(sf::Color::Black);
            break;
        case 1:
            r.setFillColor(sf::Color(255, 51, 255, 255)); // magenta
            r.setOutlineColor(sf::Color::Black);
            break;
        case 2:
            r.setFillColor(sf::Color(255, 255, 51, 255)); // yellow
            r.setOutlineColor(sf::Color::Black);
            break;
        case 3:
            r.setFillColor(sf::Color(51, 255, 51, 255)); // green
            r.setOutlineColor(sf::Color::Black);
            break;
        case 4:
            r.setFillColor(sf::Color(255, 51, 51, 255)); // red
            r.setOutlineColor(sf::Color::Black);
            break;
        case 5:
            r.setFillColor(sf::Color(51, 51, 255, 255)); // blue
            r.setOutlineColor(sf::Color::Black);
            break;
        case 6:
            r.setFillColor(sf::Color(255, 255, 255, 255)); // white
            r.setOutlineColor(sf::Color::Black);
            break;
        case 7:
            r.setFillColor(sf::Color(0, 0, 0, 255)); // black with white outline
            r.setOutlineColor(sf::Color::White);
            break;
        default:
            r.setFillColor(sf::Color(255, 255, 255, 255)); // white
            break;
    }
}
