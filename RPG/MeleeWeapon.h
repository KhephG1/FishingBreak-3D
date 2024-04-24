#ifndef MELEEEWEAPON_H
#define MELEEWEAPON_H
#include "Weapon.h"
class MeleeWeapon :
    public Weapon
{
private:
protected:

public:
    MeleeWeapon(unsigned value, std::string texture_file);
    virtual ~MeleeWeapon();
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
    virtual MeleeWeapon* clone() = 0;
};

#endif
