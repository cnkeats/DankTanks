#include "MainMenu.h"

MainMenu::~MainMenu() {}

MainMenu::MainMenu() {
    menu_state = _SelectingMap;

    PopulateMenuMap();
}

// Main game loop calls this update function
void MainMenu::Update() {
    WrapAroundSelected(p1_selected);
    WrapAroundSelected(p2_selected);

    int x;
    int y;
    int offset;
    sf::Vertex* quad_selected;

    // Player 1's selection box
    x = p1_selected.x;
    y = p1_selected.y;
    offset = 8;

    quad_selected = &vertices[MENU_X * MENU_Y * 4];

    // define its 4 corners
    quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
    quad_selected[1].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
    quad_selected[2].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);
    quad_selected[3].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);

    // define its 4 texture coordinates
    quad_selected[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset, 0);
    quad_selected[1].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), 0);
    quad_selected[2].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
    quad_selected[3].texCoords = sf::Vector2f(MENU_SIZE_X * offset, MENU_SIZE_Y);

    if (menu_state == _SelectingMap) {
        debug_string += "Select Map";
    } else if (menu_state == _SelectingColor) {
        debug_string += "Select Color (Player 1 and 2)";

        // Player 2's selection box
        x = p2_selected.x;
        y = p2_selected.y;
        offset = 9;

        quad_selected = &vertices[(MENU_X * MENU_Y + 1) * 4];

        // define its 4 corners
        quad_selected[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
        quad_selected[1].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
        quad_selected[2].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);
        quad_selected[3].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);

        // define its 4 texture coordinates
        quad_selected[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset, 0);
        quad_selected[1].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), 0);
        quad_selected[2].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
        quad_selected[3].texCoords = sf::Vector2f(MENU_SIZE_X * offset, MENU_SIZE_Y);
    }
}

// Populate menu boxes that will be drawn when this object is drawn
void MainMenu::PopulateMenuMap() {
    p1_selected = sf::Vector2i(0, 0);
    p2_selected = sf::Vector2i(0, 0);

    // load the tileset texture
    if (!menu_textures.loadFromFile(MENU_MAP_FILE)) {
        //TODO
    }

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize((MENU_X * MENU_Y + 2) * 4);

    int offset = 0;

    // populate the vertex array, with one quad per tile
    for (int y = 0; y < MENU_Y; ++y) {
        for (int x = 0; x < MENU_X; ++x) {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(x + y * MENU_X) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
            quad[1].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, y * MENU_SIZE_Y + (y + 1) * PADDING);
            quad[2].position = sf::Vector2f((x + 1) * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);
            quad[3].position = sf::Vector2f(x * MENU_SIZE_X + (x + 1) * PADDING, (y + 1) * MENU_SIZE_Y + (y + 1) * PADDING);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(MENU_SIZE_X * offset, 0);
            quad[1].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), 0);
            quad[2].texCoords = sf::Vector2f(MENU_SIZE_X + (MENU_SIZE_X * offset), MENU_SIZE_Y);
            quad[3].texCoords = sf::Vector2f(MENU_SIZE_X * offset, MENU_SIZE_Y);

            offset++;
        }
    }
}

// Change texture of menu tiles, position is unchanged
void MainMenu::PopulateMenuColor() {
    p1_selected = sf::Vector2i(0, 0);
    p2_selected = sf::Vector2i(0, 0);

    // load the tileset texture
    if (!menu_textures.loadFromFile(MENU_COLOR_FILE)) {
        //TODO
    }

    menu_state = _SelectingColor;
}

// Virtual draw
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // texture
    states.texture = &menu_textures;

    // draw the vertex array
    target.draw(vertices, states);
}

// Make menu movements wrap around all sides
void MainMenu::WrapAroundSelected(sf::Vector2i &v) {
    if (v.x < 0) {
        v.x = MENU_X - 1;
    } else if (v.x >= MENU_X) {
        v.x = 0;
    }

    if (v.y < 0) {
        v.y = MENU_Y - 1;
    } else if (v.y >= MENU_Y) {
        v.y = 0;
    }
}

// Return P1's current selected coordinates
sf::Vector2i MainMenu::InputP1Select() {
    sf::Vector2i ret_selected = p1_selected;
    if (menu_state == _SelectingMap) {
        PopulateMenuColor();
    }

    return ret_selected;
}

// Move P1's selection up
void MainMenu::InputP1Up() {
    p1_selected.y++;
}

// Move P1's selection down
void MainMenu::InputP1Down() {
    p1_selected.y--;
}

// Move P1's selection left
void MainMenu::InputP1Left() {
    p1_selected.x--;
}

// Move P1's selection right
void MainMenu::InputP1Right() {
    p1_selected.x++;
}

// Return P2's current selected coordinates
sf::Vector2i MainMenu::InputP2Select() {
    sf::Vector2i ret_selected = p2_selected;

    return ret_selected;
}

// Move P2's selection up
void MainMenu::InputP2Up() {
    p2_selected.y++;
}

// Move P2's selection down
void MainMenu::InputP2Down() {
    p2_selected.y--;
}

// Move P2's selection left
void MainMenu::InputP2Left() {
    p2_selected.x--;
}

// Move P2's selection right
void MainMenu::InputP2Right() {
    p2_selected.x++;
}
