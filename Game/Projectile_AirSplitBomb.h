#include "Globals.h"
#include "Projectile.h"

class Projectile_AirSplitBomb : public Projectile {
public:
    Projectile_AirSplitBomb(sf::Vector2f, sf::Vector2f);
    Projectile_AirSplitBomb(sf::Vector2f, sf::Vector2f, float, int);
    Projectile_AirSplitBomb(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile_AirSplitBomb() {};
    virtual void PostUpdate(TileMap* &);
private:
    static const int STARTING_TICKS_UNTIL_SPLIT = 2;
    int ticks_until_split;
};
