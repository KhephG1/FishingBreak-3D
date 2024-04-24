#include "stdafx.h"
#include "Enemy.h"


Enemy::~Enemy()
{
}


void Enemy::initVariables()
{
	gainEXP = 10;
}

void Enemy::initAnimations()
{
	

}
//constructors / destructors
Enemy::Enemy( ) {
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

const unsigned& Enemy::getGainExp() const
{
	return gainEXP;
}


