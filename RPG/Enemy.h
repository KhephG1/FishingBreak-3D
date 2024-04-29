#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"
#include "AIFollow.h"
class EnemySpawnerTile;
class Enemy: public Entity
{
protected:
	//Variables
	//EnemySpawner& spawner;
	//initializers
	EnemySpawnerTile& enemySpawnerTile;
	unsigned gainEXP;
	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;
	virtual void initVariables();
	virtual void initAnimations();
public:
	Enemy(EnemySpawnerTile& spawnerTile);
	virtual ~Enemy();
	virtual void damage(const int damage);
	virtual const AttributeComponent* getAttributeComponent();
	virtual void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position = sf::Vector2f{})= 0;
	virtual void update(const float& dt, sf::Vector2f mousePosView);
	virtual void updateAnimation(const float& dt) = 0;
	virtual const bool dead();
	virtual void generateAttributes(const unsigned lvl);
	const unsigned& getGainExp() const;
	EnemySpawnerTile& getSpawnerTile();
	void resetDamageTimer();
	const bool getDamageTimerDone() const;
};

#endif