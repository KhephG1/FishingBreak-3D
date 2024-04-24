#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	range = 20;
	damageMax = 2;
	damageMin = 1;
	//Timer
	attackTimer.restart();
	//500 milliseconds
	attackTimerMax = 500;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(unsigned value, std::string texture_file): Item{value}
{
	initVariables();
	if (!weaponTexture.loadFromFile(texture_file)) {
		std::cout << "weapon loading failed" << std::endl;
	}
	weaponSprite.setTexture(weaponTexture);
	
}

const unsigned Weapon::getRange() const
{
	return range; 
}

const unsigned& Weapon::getDamageMin() const
{
	return damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return damageMax;
}

const bool Weapon::getattackTimer()
{
	if (attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax) {
		attackTimer.restart();
		return true;
	}
	return false;
}



