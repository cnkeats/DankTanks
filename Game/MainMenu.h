#include "Globals.h"

class MainMenu : public sf::Drawable, public sf::Transformable {
public:
    MainMenu();
    ~MainMenu();
    void Update();
    int InputP1Select();
    void InputP1Up();
    void InputP1Down();
    void InputP1Left();
    void InputP1Right();
    int InputP2Select();
    void InputP2Up();
    void InputP2Down();
    void InputP2Left();
    void InputP2Right();

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void PopulateMenuMap();
    void PopulateMenuClass();
    void WrapAroundSelected(int &);

    enum MenuState {_SelectingClass, _SelectingMap};
    MenuState menu_state;

    static const int MENU_X = 4;
    static const int MENU_SIZE_X = 384;
    static const int MENU_SIZE_Y = 216;
    static const int PADDING = 77;
    bool p1_selected_class;
    bool p2_selected_class;
    int p1_selected;
    int p2_selected;
    sf::VertexArray vertices;
    sf::Texture menu_textures;

    sf::RectangleShape r_map;
    sf::RectangleShape r_p1;
    sf::RectangleShape r_p2;
};
