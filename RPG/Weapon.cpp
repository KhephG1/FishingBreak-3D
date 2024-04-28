#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	range = 50;
	damageMax = 5;
	damageMin = 1;
	//Timer
	attackTimer.restart();
	//500 milliseconds
	attackTimerMax = 500;
}

Weapon::~Weapon()
{
}

Weapon::Weapon(unsigned level,unsigned value, std::string texture_file): Item{level,value}
{
	initVariables();
	if (!weaponTexture.loadFromFile(texture_file)) {
		std::cout << "weapon loading failed" << std::endl;
	}
	weaponSprite.setTexture(weaponTexture);
	
}

Weapon::Weapon(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range, unsigned value, std::string texture_file): Item{level,value}
{
}

const unsigned Weapon::getRange() const
{
	return range; 
}

const unsigned& Weapon::getDamageMin() const
{
	return damageMin;
}

const unsigned Weapon::getDamageDynamic() const
{
	return rand() % (damageMax - damageMin + 1) + damageMin;
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



