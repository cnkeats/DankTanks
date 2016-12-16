#include "Globals.h"
#include "Projectile.h"

class Projectile_Teleport : public Projectile {
public:
    Projectile_Teleport(sf::Vector2f, sf::Vector2f);
    ~Projectile_Teleport();
    virtual bool IsTeleportedInBounds();
private:

};
