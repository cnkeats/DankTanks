#include "Globals.h"
#include "Projectile.h"

class Projectile_Teleport : public Projectile {
public:
    Projectile_Teleport(sf::Vector2f, sf::Vector2f);
    Projectile_Teleport(sf::Vector2f, sf::Vector2f, float, int);
    Projectile_Teleport(sf::Vector2f, sf::Vector2f, float, int, float, int);
    virtual ~Projectile_Teleport() {};
    virtual void PostHit(TileMap* &);
    virtual bool IsTeleportedInBounds();
private:

};
