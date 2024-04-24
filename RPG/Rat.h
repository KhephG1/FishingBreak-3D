#ifndef RAT_H
#define RAT_H
#include "Enemy.h"
class Rat :
    public Enemy
{
private:
    void initVariables();
    void initAnimations();
public:
    Rat(float xpos, float ypos, sf::Texture* tex_sheet);
    virtual~Rat();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f mousePosView);

    void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position);

};

#endif