#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int lvl)
{
	level = lvl;
	exp = 0;
	//expNext equation
	/*
	
	
	*/
	expNext = static_cast<unsigned>((50/3) * (std::pow(level,3) - 6 * std::pow(level,2) + (level * 22) -12));
	AttributePts = 3;

	vitality = 1;
	strength = 1;
	agility = 1;
	intelligence = 1;
	dexterity = 1;
	updateStats(true);

}

AttributeComponent::~AttributeComponent()
{
	
}

void AttributeComponent::updateStats(const bool reset)
{
	hpMax = vitality * 9 + strength * 2;
	//Format: main contributor * multiplying factor : secondary contributor / attributes required to increment : tertiary contributor / larger divisor
	damageMax = strength * 2 + strength / 2 + intelligence / 5;
	damageMin = strength * 2 + strength / 4 + intelligence / 5;
	accuracy = dexterity * 5 + dexterity / 3 + intelligence / 5;
	defense = agility * 2 + agility / 4 + intelligence / 5;
	luck = intelligence * 2 + intelligence / 5;
	if (reset) {
		hp = hpMax;
	}
}


void AttributeComponent::updateLvl()
{
	while (exp >= expNext) {
		++level;
		exp -= expNext;
		expNext = static_cast<unsigned>((50 / 3) * (std::pow(level + 1, 3) - 6 * std::pow(level+ 1, 2) + (level * 21) - 12));
		++AttributePts;
	}
}

void AttributeComponent::update()
{

}

void AttributeComponent::gainExp(const unsigned ex)
{
	exp += ex;
	updateLvl();
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << level << "\n"
		<< "EXP: " << exp << "\n"
		<< "Exp Next: " << expNext << "\n"
		<< "Attribute pts: " << AttributePts << "\n";
	return ss.str();
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;
	if (hp < 0) {
		this->hp = 0;
	}
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;
	if (hp > hpMax) {
		this->hp = hpMax;
	}
}


void AttributeComponent::loseXP(const int xp)
{
	exp -= xp;
	if (exp < 0) {
		exp = 0;
	}
}
