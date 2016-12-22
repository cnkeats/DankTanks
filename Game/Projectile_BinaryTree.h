#include "Globals.h"
#include "Projectile.h"

class Projectile_BinaryTree : public Projectile {
public:
    Projectile_BinaryTree(sf::Vector2f, sf::Vector2f);
    Projectile_BinaryTree(sf::Vector2f, sf::Vector2f, float, int);
    Projectile_BinaryTree(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile_BinaryTree() {};
    virtual void PostUpdate(TileMap* &);
private:
    static const int STARTING_TICKS_UNTIL_SPLIT = 30;
    int ticks_until_split;
};