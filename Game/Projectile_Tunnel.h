#include "Globals.h"
#include "Projectile.h"

class Projectile_Tunnel : public Projectile {
public:
    Projectile_Tunnel(sf::Vector2f, sf::Vector2f);
    virtual ~Projectile_Tunnel() {};
    virtual void PostHit(TileMap* &);
private:

};
