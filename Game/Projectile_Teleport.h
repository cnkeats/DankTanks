#include "Globals.h"
#include "Projectile.h"

class Projectile_Teleport : public Projectile {
public:
    Projectile_Teleport(sf::Vector2f, sf::Vector2f);
    virtual ~Projectile_Teleport() {};
    virtual void PostHit(TileMap* &);
    virtual bool IsTeleportedInBounds();
private:

};
