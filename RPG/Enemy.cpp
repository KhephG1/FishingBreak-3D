#include "stdafx.h"
#include "Enemy.h"


Enemy::~Enemy()
{
}


void Enemy::initVariables()
{

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

const bool Enemy::dead()
{
	if (attributeComponent) {
		return attributeComponent->dead();
	}
}

void Enemy::generateAttributes(const unsigned lvl)
{
	gainEXP = lvl * (rand() % 5 + 1);
}

const unsigned& Enemy::getGainExp() const
{
	return gainEXP;
}

EnemySpawnerTile& Enemy::getSpawnerTile()
{
	return enemySpawnerTile;
}


