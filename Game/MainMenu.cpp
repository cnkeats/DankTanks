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

    UpdateP1Selection();
    UpdateP2Selection();
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

// Return P1's current selected coordinates
GameStartingInfo MainMenu::InputP1Select() {
    if (menu_state == _SelectingClass) {
        game_starter.p1_class_index = p1_selected;
        game_starter.p1_color_index = p1_selected;
    } else if (menu_state == _SelectingMap) {
        game_starter.map_index = p1_selected;
    }

    return game_starter;
}

// Input back button
void MainMenu::InputP1Back() {
    if (menu_state == _SelectingClass) {
        game_starter.p1_class_index = -1;
        game_starter.p1_color_index = -1;
    } else if (menu_state == _SelectingMap) {
        PopulateClasses();
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

// Return P2's current selected coordinates
GameStartingInfo MainMenu::InputP2Select() {
    if (menu_state == _SelectingClass) {
        game_starter.p2_class_index = p2_selected;
        game_starter.p2_color_index = p2_selected;
    } else if (menu_state == _SelectingMap) {
        game_starter.map_index = p2_selected;
    }

    return game_starter;
}

// Input back button
void MainMenu::InputP2Back() {
    if (menu_state == _SelectingClass) {
        game_starter.p2_class_index = -1;
        game_starter.p2_color_index = -1;
    } else if (menu_state == _SelectingMap) {
        PopulateClasses();
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
