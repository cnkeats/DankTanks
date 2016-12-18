#include "Globals.h"

class MainMenu : public sf::Drawable, public sf::Transformable {
public:
    MainMenu();
    ~MainMenu();
    void Update();
    sf::Vector2i InputP1Select();
    void InputP1Up();
    void InputP1Down();
    void InputP1Left();
    void InputP1Right();
    sf::Vector2i InputP2Select();
    void InputP2Up();
    void InputP2Down();
    void InputP2Left();
    void InputP2Right();

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void PopulateMenuMap();
    void PopulateMenuColor();
    void WrapAroundSelected(sf::Vector2i &);

    enum MenuState {_SelectingMap, _SelectingColor};
    MenuState menu_state;

    static const int MENU_X = 4;
    static const int MENU_Y = 2;
    static const int MENU_SIZE_X = 384;
    static const int MENU_SIZE_Y = 216;
    static const int PADDING = 77;
    sf::Vector2i p1_selected;
    sf::Vector2i p2_selected;
    sf::VertexArray vertices;
    sf::Texture menu_textures;
};
