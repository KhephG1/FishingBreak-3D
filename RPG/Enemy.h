#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"
class EnemySpawnerTile;
class Enemy: public Entity
{
private:
	//Variables
	//EnemySpawner& spawner;
	//initializers
	unsigned gainEXP;
	virtual void initVariables();
	virtual void initAnimations();
public:
	Enemy();
	virtual ~Enemy();
	virtual void damage(const int damage);
	virtual const AttributeComponent* getAttributeComponent();
	virtual void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position = sf::Vector2f{})= 0;
	virtual void update(const float& dt, sf::Vector2f mousePosView) = 0;
	virtual void updateAnimation(const float& dt) = 0;
	virtual const bool dead();
	const unsigned& getGainExp() const;

};

#endif