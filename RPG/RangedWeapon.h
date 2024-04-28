#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H
#include "Weapon.h"
class RangedWeapon :
    public Weapon
{
private:
protected:

public:
    RangedWeapon(unsigned level,unsigned value, std::string texture_file);
    virtual~RangedWeapon();
    virtual RangedWeapon* clone() = 0;
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
    void generate(const unsigned level_min, const unsigned level_max);
};
#endif
