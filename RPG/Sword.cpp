#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned value, std::string texture_file):MeleeWeapon{value, texture_file}
{
	
	weaponSprite.setOrigin(weaponSprite.getGlobalBounds().width / 2.f, weaponSprite.getGlobalBounds().height);
	type = MELEEWEAPON;
}

Sword::~Sword()
{
}

void Sword::update(const sf::Vector2f& mousePosView, const sf::Vector2f center)
{
	weaponSprite.setPosition(center.x, center.y);
	float dX{ mousePosView.x - weaponSprite.getPosition().x };
	float dY{ mousePosView.y - weaponSprite.getPosition().y };
	float angle = atan2(dY, dX) * 180 / (4 * atan(1));

	weaponSprite.setRotation(angle + 90);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader) {
		target.draw(weaponSprite, shader);
	}
	else {
		target.draw(weaponSprite);
	}
}

Sword* Sword::clone()
{
	return new Sword{ *this };
}
