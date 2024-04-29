#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned level,unsigned value, std::string texture_file):MeleeWeapon{level,value, texture_file}
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

	if (attackTimer.getElapsedTime().asMilliseconds() < attackTimerMax/4) {
		float magnitude = std::sqrt(std::pow(dX, 2) + std::powf(dY, 2));
		sf::Vector2f normalized{ dX / magnitude, dY / magnitude };
		weaponSprite.setPosition(center.x + normalized.x*10.f, center.y + normalized.y * 10.f);
	}
	else {
		weaponSprite.setRotation(angle + 90);
	}
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
