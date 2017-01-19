#include "MainMenu.h"

MainMenu::~MainMenu() {}

MainMenu::MainMenu() {
    PopulateMenuClass();

    r_map.setFillColor(sf::Color::White);
    r_map.setPosition(sf::Vector2f(448, PADDING));
    r_map.setSize(sf::Vector2f(1024, 576));

    r_p1.setFillColor(sf::Color::Red);
    r_p1.setPosition(sf::Vector2f(PADDING, PADDING));
    r_p1.setSize(sf::Vector2f(845, 475));

    r_p2.setFillColor(sf::Color::Blue);
    r_p2.setPosition(sf::Vector2f(845 + 2 * PADDING, PADDING));
    r_p2.setSize(sf::Vector2f(845, 475));
    //r_p2.setTexture(&menu_textures);
}

// Main game loop calls this update function
void MainMenu::Update() {
    WrapAroundSelected(p1_selected);
    WrapAroundSelected(p2_selected);

    // If both players have selected a class, go to map selection
    if (menu_state == _SelectingClass && p1_selected_class && p2_selected_class) {
        PopulateMenuMap();
    }

    if (menu_state == _SelectingClass) {
        debug_string += "Select Color (Player 1 and 2)";

        window.draw(r_p1);
        window.draw(r_p2);

        // Define player 1's selector brackets
        int x = p1_selected;
        sf::Vertex* quad_selected = &vertices[MENU_X * 6];

        // define its 4 corners
        quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[1].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[2].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - PADDING);
        quad_selected[3].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[4].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
        quad_selected[5].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);

        // Player 2's selector brackets
        x = p2_selected;
        quad_selected = &vertices[(MENU_X + 1) * 6];

        // define its 4 corners
        quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[1].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[2].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - PADDING);
        quad_selected[3].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[4].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
        quad_selected[5].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
    } else if (menu_state == _SelectingMap) {
        debug_string += "Select Map";

        window.draw(r_map);

        // Define player 1's selector brackets
        int x = p1_selected;
        sf::Vertex* quad_selected = &vertices[MENU_X * 6];

        // define its 4 corners
        quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[1].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[2].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - PADDING);
        quad_selected[3].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[4].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
        quad_selected[5].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);

        // Player 2's selector brackets on top of player 1 since both players can move it during map selection
        quad_selected = &vertices[(MENU_X + 1) * 6];

        // define its 4 corners
        quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[1].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[2].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - PADDING);
        quad_selected[3].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - MENU_SIZE_Y - PADDING);
        quad_selected[4].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
        quad_selected[5].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
    }
}

// Populate menu boxes that will be drawn when this object is drawn
void MainMenu::PopulateMenuMap() {
    menu_state = _SelectingMap;

    p1_selected = 0;
    p2_selected = 0;

    // Load texture for map selections
    if (!menu_textures.loadFromFile("menu_map.png")) {
        //TODO
    }
}

// Change texture of menu tiles, position is unchanged
void MainMenu::PopulateMenuClass() {
    menu_state = _SelectingClass;

    // These are set to true when each player selects a class
    p1_selected_class = false;
    p2_selected_class = false;

    p1_selected = 0;
    p2_selected = 0;

    // Load texture for class selections
    if (!menu_textures.loadFromFile("menu_class.png")) {
        //TODO
    }

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::TrianglesStrip);
    vertices.resize((MENU_X + 2) * 6);

    int offset = 0;

    // Define the 4 rectangles for classes and maps
    for (int x = 0; x < MENU_X; ++x) {
        // get a pointer to the current tile's quad
        sf::Vertex* quad = &vertices[(x) * 6];

        quad[0].color = sf::Color::Transparent;
        quad[5].color = sf::Color::Transparent;

        // define its 4 corners
        quad[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad[1].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - MENU_SIZE_Y - PADDING);
        quad[2].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING      , window.getSize().y - PADDING);
        quad[3].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - MENU_SIZE_Y - PADDING);
        quad[4].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);
        quad[5].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, window.getSize().y - PADDING);

        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , 0);
        quad[1].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , 0);
        quad[2].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y);
        quad[3].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), 0);
        quad[4].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
        quad[5].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);

        offset++;
    }

    // Define texture for player 1's selector brackets
    offset = 0;
    sf::Vertex* quad_selected = &vertices[MENU_X * 6];

    quad_selected[0].color = sf::Color::Transparent;
    quad_selected[5].color = sf::Color::Transparent;

    // define its 4 texture coordinates
    quad_selected[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y);
    quad_selected[1].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y);
    quad_selected[2].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y * 2);
    quad_selected[3].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
    quad_selected[4].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y * 2);
    quad_selected[5].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y * 2);

    // Define texture for player 2's selector brackets
    offset = 1;

    quad_selected = &vertices[(MENU_X + 1) * 6];

    quad_selected[0].color = sf::Color::Transparent;
    quad_selected[5].color = sf::Color::Transparent;

    // define its 4 texture coordinates
    quad_selected[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y);
    quad_selected[1].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y);
    quad_selected[2].texCoords = sf::Vector2f(MENU_SIZE_X * offset                , MENU_SIZE_Y * 2);
    quad_selected[3].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
    quad_selected[4].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y * 2);
    quad_selected[5].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y * 2);
}

// Virtual draw
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // texture
    states.texture = &menu_textures;

    // draw the vertex array
    target.draw(vertices, states);
}

// Make menu movements wrap around all sides
void MainMenu::WrapAroundSelected(int &i) {
    if (i < 0) {
        i = MENU_X - 1;
    } else if (i >= MENU_X) {
        i = 0;
    }
}

// Return P1's current selected coordinates
int MainMenu::InputP1Select() {
    p1_selected_class = true;

    return p1_selected;
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
    p1_selected--;
}

// Move P1's selection right
void MainMenu::InputP1Right() {
    p1_selected++;
}

// Return P2's current selected coordinates
int MainMenu::InputP2Select() {
    if (menu_state == _SelectingClass) {
        p2_selected_class = true;

        return p2_selected;
    } else if (menu_state == _SelectingMap) {
        return p1_selected;
    } else {
        return -1;
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
    if (menu_state == _SelectingClass) {
        p2_selected--;
    } else if (menu_state == _SelectingMap) {
        p1_selected--;
    }
}

// Move P2's selection right
void MainMenu::InputP2Right() {
    if (menu_state == _SelectingClass) {
        p2_selected++;
    } else if (menu_state == _SelectingMap) {
        p1_selected++;
    }
}
