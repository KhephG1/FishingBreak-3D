#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	if (!weaponTexture.loadFromFile("Resources/Images/Player/sword.png")) {
		std::cout << "weapon loading failed" << std::endl;
	}
	weaponSprite.setTexture(weaponTexture);
	weaponSprite.setOrigin(weaponSprite.getGlobalBounds().width / 2.f, weaponSprite.getGlobalBounds().height);
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
