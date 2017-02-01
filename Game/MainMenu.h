#include "Globals.h"
#include "GameStartingInfo.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();
    void Update();
    void InputP1(int);
    GameStartingInfo InputP1Select();
    void InputP2(int);
    GameStartingInfo InputP2Select();

private:
    void PopulateClasses();
    void PopulateMaps();
    void UpdateP1Selection();
    void UpdateP2Selection();
    void UpdateInput();
    void SetColor(sf::RectangleShape &, int);

    void InputP1Left();
    void InputP1Right();
    void InputP1Up();
    void InputP1Down();
    void InputP1ColorUp();
    void InputP1Back();
    void InputP1ColorDown();

    void InputP2Left();
    void InputP2Right();
    void InputP2Up();
    void InputP2Down();
    void InputP2ColorUp();
    void InputP2Back();
    void InputP2ColorDown();

    enum MenuState {_SelectingClass, _SelectingMap};
    MenuState menu_state;

    static const int MENU_X = 4;
    static const int THUMBNAIL_SIZE_X = 384;
    static const int THUMBNAIL_SIZE_Y = 216;
    static const int CLASS_PREVIEW_SIZE_X = 845;
    static const int CLASS_PREVIEW_SIZE_Y = 475;
    static const int MAP_PREVIEW_SIZE_X = 1024;
    static const int MAP_PREVIEW_SIZE_Y = 576;
    static const int PADDING = 77;
    GameStartingInfo game_starter;
    int p1_selected;
    int p2_selected;
    int p1_input_cooldown[8];
    int p2_input_cooldown[8];
    bool p1_input_status[8];
    bool p2_input_status[8];
    sf::RectangleShape p1_color_rectangle;
    sf::RectangleShape p2_color_rectangle;

    // Selectors
    std::vector<sf::Texture*> selector_textures;
    std::vector<sf::RectangleShape*> selectors;

    // Class tiles at bottom
    std::vector<sf::Texture*> class_textures;
    std::vector<sf::RectangleShape*> class_tiles;

    // Class previews
    std::vector<sf::Texture*> class_preview_textures;
    std::vector<sf::RectangleShape*> class_previews;

    // Map tiles at bottom
    std::vector<sf::Texture*> map_textures;
    std::vector<sf::RectangleShape*> map_tiles;

    // Map preview
    std::vector<sf::Texture*> map_preview_textures;
    sf::RectangleShape map_preview;
};
