#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned value, std::string texture_file):RangedWeapon{value, texture_file}
{
	type = RANGEDWEAPON;
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	//Damn
	return new Bow{*this};
}

void Bow::update(const sf::Vector2f& mousePosView, const sf::Vector2f center)
{
}

void Bow::render(sf::RenderTarget& target, sf::Shader* shader)
{
}
