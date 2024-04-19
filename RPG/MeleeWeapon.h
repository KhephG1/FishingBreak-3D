#ifndef MELEEEWEAPON_H
#define MELEEWEAPON_H
#include "Item.h"
class MeleeWeapon :
    public Item
{
private:
protected:
    bool attacking;
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    int damageMin;
    int damageMax;
public:
    MeleeWeapon();
    virtual ~MeleeWeapon();
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif
