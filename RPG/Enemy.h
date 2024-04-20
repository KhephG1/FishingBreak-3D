#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h"
class EnemySpawner;
class Enemy: public Entity
{
private:
	//Variables
	EnemySpawner& spawner;
	//initializers
	void initVariables();
	void initAnimations();
public:
	Enemy(EnemySpawner& enemySpawner,float xpos, float ypos, sf::Texture* tex_sheet);
	virtual ~Enemy();

	void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position = sf::Vector2f{});
	void update(const float& dt, sf::Vector2f mousePosView);
	void updateAnimation(const float& dt);
};

#endif