#include "Globals.h"
#include "Projectile.h"
#include "Projectile_Bomb.h"

class Projectile_ImpactSplitBomb : public Projectile {
public:
    Projectile_ImpactSplitBomb(sf::Vector2f, sf::Vector2f);
    ~Projectile_ImpactSplitBomb();
    virtual void Update(TileMap* &);
    virtual void PostHit(TileMap* &);
private:
    std::vector<Projectile*> sub_projectiles;
    bool is_split;
};
