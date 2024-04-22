#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h"
class EnemySpawner;
class Enemy: public Entity
{
private:
	//Variables
	//EnemySpawner& spawner;
	//initializers
	virtual void initVariables();
	virtual void initAnimations();
public:
	Enemy();
	virtual ~Enemy();

	virtual void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position = sf::Vector2f{})= 0;
	virtual void update(const float& dt, sf::Vector2f mousePosView) = 0;
	virtual void updateAnimation(const float& dt) = 0;
};

#endif