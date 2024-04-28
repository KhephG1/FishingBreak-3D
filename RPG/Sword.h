#ifndef SWORD_H
#define SWORD_H
#include "MeleeWeapon.h"
class Sword :
    public MeleeWeapon
{
public:
    Sword(unsigned level,unsigned value, std::string texture_file);
    virtual ~Sword();
    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center) override;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) override;
    virtual Sword* clone();
};

#endif