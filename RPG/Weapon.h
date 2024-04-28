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
    Weapon(unsigned level,unsigned value, std::string texture_file);
    Weapon(unsigned level,unsigned damage_min,unsigned damage_max,unsigned range,unsigned value, std::string texture_file);
    virtual Item* clone()=0;
    virtual void generate(const unsigned lvl_max, const unsigned level_min) = 0;
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
    const unsigned getRange() const;
    const unsigned& getDamageMin() const;
    const unsigned getDamageDynamic() const;
    const unsigned& getDamageMax() const;
    const bool getattackTimer();

};

#endif