#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
class Weapon :
    public Item
{
private:
    void initVariables();
protected:
    unsigned range;
    bool attacking;
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    int damageMin;
    int damageMax;
    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;
 
public:
    virtual ~Weapon();
    Weapon(unsigned value, std::string texture_file);
    virtual Item* clone()=0;
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
    const unsigned getRange() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const bool getattackTimer();

};

#endif