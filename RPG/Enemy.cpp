#include "stdafx.h"
#include "Enemy.h"


Enemy::~Enemy()
{
}


void Enemy::initVariables()
{
	gainEXP = 10;
	damageTimerMax = 1000;
}

void Enemy::initAnimations()
{
	

}
//constructors / destructors
Enemy::Enemy(EnemySpawnerTile& spawnerTile) : enemySpawnerTile{ spawnerTile } {
	initVariables();
	initAnimations();
}

void Enemy::damage(const int damage)
{
	if(attributeComponent)
		attributeComponent->loseHP(damage);
}

const AttributeComponent* Enemy::getAttributeComponent()
{
	if (attributeComponent) {
		return attributeComponent;
	}
	std::cout << "ERROR:::ENEMY::GETATTRIBUTE COMPONENT IS NULLPTR";
	return nullptr;
}

void Enemy::update(const float& dt, sf::Vector2f mousePosView)
{
}

const bool Enemy::dead()
{
	if (attributeComponent) {
		return attributeComponent->dead();
	}
}

void Enemy::generateAttributes(const unsigned lvl)
{
	gainEXP = lvl * (rand() % 50 + 10);
}

const unsigned& Enemy::getGainExp() const
{
	return gainEXP;
}

EnemySpawnerTile& Enemy::getSpawnerTile()
{
	return enemySpawnerTile;
}

void Enemy::resetDamageTimer()
{
	damageTimer.restart();
}

const bool Enemy::getDamageTimerDone() const
{
	return damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax;
}


